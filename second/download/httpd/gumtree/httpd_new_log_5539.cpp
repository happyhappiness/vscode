fprintf(stderr, "Could not spawn post-rotate process '%s': %s\n",
                config->postrotate_prog,
                apr_strerror(rv, error, sizeof(error)));