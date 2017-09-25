        if (apr_fnmatch_test(path)) {
            fprintf(stderr, "%s: wildcard patterns not allowed in Include "
                    "%s\n", ap_server_argv0, fname);
            exit(1);
        }

        if (!ap_is_directory(p, path)){ 
            fprintf(stderr, "%s: Include directory '%s' not found",
                    ap_server_argv0, path);
            exit(1);
        }

        if (!apr_fnmatch_test(pattern)) {
