#include <iostream>

#include <Fst.h>
#include <types.h>

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

    std::vector<std::pair<std::string, u64>> input{
        {"hello", 1},
        {"hel", 4},
        {"q", 33},
        {"za", 13}
    };

    Surf::Fst fst(input);


    Surf::value_t* value = fst.exactKeySearch("hel");
    if(value) {
        std::cout << "Find key, value: " << *value << '\n';
    } else {
        std::cout << "No key\n";
    }

    std::cout << "Work done, shutdown application" << std::endl;
    return 0;
}
