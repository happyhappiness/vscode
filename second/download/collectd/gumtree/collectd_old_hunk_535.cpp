
#include "collectd.h"
#include "common.h"
#include "plugin.h"

#include "utils_parse_option.h"

#define print_to_socket(fh, ...) \
    do { \
        if (fprintf (fh, __VA_ARGS__) < 0) { \
            char errbuf[1024]; \
            WARNING ("handle_putval: failed to write to socket #%i: %s", \
