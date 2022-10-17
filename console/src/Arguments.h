#include <Application/Args.h>

#define ARG_HELP "help"
#define ARG_HELP_SHORT "h"

#define ARG_TEST "test"
#define ARG_TEST_SHORT "t"

void buildArgs(Args &args) {
    args.add({ARG_HELP, ARG_HELP_SHORT}, "Print help message");
    args.add({ARG_TEST, ARG_TEST_SHORT}, "Run assert tests");
}