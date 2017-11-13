fprintf(stderr,
                "post_rotate: apr_procattr_create failed for '%s': %s\n",
                config->postrotate_prog,
                apr_strerror(rv, error, sizeof(error)));