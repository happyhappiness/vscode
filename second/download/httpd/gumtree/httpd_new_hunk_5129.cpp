        apr_file_remove(config->linkfile, newlog->pool);
        if (config->verbose) {
            fprintf(stderr,"Linking %s to %s\n", newlog->name, config->linkfile);
        }
        rv = apr_file_link(newlog->name, config->linkfile);
        if (rv != APR_SUCCESS) {
            apr_strerror(rv, error, sizeof error);
            fprintf(stderr, "Error linking file %s to %s (%s)\n",
                    newlog->name, config->linkfile, error);
            exit(2);
        }
    }
