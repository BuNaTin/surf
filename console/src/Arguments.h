#include <Application/Args.h>

#define ARG_LONG_HELP "help"
#define ARG_HELP "h"


void buildArgs(Args &args) {
    args.add({ARG_LONG_HELP, ARG_HELP}, "Print help message");
}
