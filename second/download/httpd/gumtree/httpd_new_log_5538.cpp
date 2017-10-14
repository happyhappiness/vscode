fprintf(stderr,
                "post_rotate: could not set up process attributes for '%s': %s\n",
                config->postrotate_prog,
                apr_strerror(rv, error, sizeof(error)));