#include <iostream>

#include <Fst.h>
#include <surfTypes.h>

#include <test.h>
#include <Arguments.h>
bool processArgs(Args &args, int argc, char *argv[]) noexcept {
    try {
        buildArgs(args);
        args.process(argc, argv);
    } catch (Args::WrongArgument &err) {
        std::cerr << err.what() << std::endl;
        return false;
    } catch (Args::ErrorChecking &err) {
        std::cerr << err.what() << std::endl;
        return false;
    } catch (...) {
        std::cerr << "Unhandeled exception while parsing args"
                  << std::endl;
        return false;
    }

    return true;
}

bool checkKey(Surf::Fst &fst, const std::string &key) {
    Surf::value_t *value = fst.exactKeySearch(key);
    if (value) {
        std::cout << "Find [" << key << "], value: " << *value << '\n';
        return true;
    } else {
        std::cout << "No   [" << key << "]\n";
        return false;
    }
}

void runTest() {
    using Surf::key_t;
    using Surf::value_t;

    std::vector<std::pair<key_t, value_t>> input{
            {"hello", 1}, {"he", 3}, {"andatra", 77}, {"a", 15}};

    Surf::Fst fst(input);

    std::vector<key_t> check_keys{"a",
                                  "many",
                                  "coco",
                                  "hello",
                                  "andatra",
                                  "andra",
                                  "andaaa"
                                  "andrameda",
                                  "yerfbierb",
                                  "123124234",
                                  "gefrgrg",
                                  "a",
                                  "a",
                                  "a$",
                                  "ay",
                                  "andatra"};

    test(fst, check_keys, input);
}

void defaultRun() {
    using Surf::key_t;
    using Surf::value_t;

    std::vector<std::pair<key_t, value_t>> input{
            {"hello", 1}, {"he", 3}, {"andatra", 77}, {"a", 15}};

    Surf::Fst fst(input);

    checkKey(fst, "a");
    checkKey(fst, "an");
    checkKey(fst, "anda");
    checkKey(fst, "az");
    checkKey(fst, "hello");
    checkKey(fst, "h");
    checkKey(fst, "he");
    checkKey(fst, "ell");
    checkKey(fst, "andatra");
    checkKey(fst, "rrrere");
}

int main(int argc, char *argv[]) {
    checkBytes(); // assert on bytes size

    Args args;
    if (!processArgs(args, argc, argv)) {
        std::cerr << args.defaultHelp() << std::endl;
        return 1;
    }

    if (args.has(ARG_HELP)) {
        std::cout << args.defaultHelp() << std::endl;
        return 0;
    }

    if (args.has(ARG_TEST)) {
        runTest();
        return 0;
    }

    defaultRun();
    std::cout << "Work done, shutdown application" << std::endl;
    return 0;
}
