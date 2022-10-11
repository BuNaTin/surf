#include <iostream>

#include <PrefixTree/Tree.h>
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

    Surf::Tree data;
    u64 value = 0;
    data.insert("Hello", 3);
    data.insert("Hell", 4);

    if (data.find("Hel", value)) {
        std::cout << "Find: " << value << '\n';
    } else {
        std::cout << "No value\n";
    }

    std::cout << "Work done, shutdown application" << std::endl;
    return 0;
}
