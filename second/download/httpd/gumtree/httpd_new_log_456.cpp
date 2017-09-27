fprintf(stderr, "%s: Directory %s exceeds the maximum include "
                    "directory nesting level of %u. You have probably a "
                    "recursion somewhere.\n", ap_server_argv0, path,
                    AP_MAX_INCLUDE_DIR_DEPTH);