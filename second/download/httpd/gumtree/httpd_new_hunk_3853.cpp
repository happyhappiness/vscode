        }

        /* This child needs the existing stderr opened for logging,
         * already
         */

        /* Read this child's generation number as soon as now,
         * so that further hooks can query it.
         */
        if (!ReadFile(pipe, &my_generation, sizeof(my_generation),
                      &BytesRead, (LPOVERLAPPED) NULL)
                || (BytesRead != sizeof(my_generation))) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_os_error(), NULL, APLOGNO(02965)
                         "Child: Unable to retrieve my generation from the parent");
            exit(APEXIT_CHILDINIT);
        }

        /* The parent is responsible for providing the
         * COMPLETE ARGUMENTS REQUIRED to the child.
         *
         * No further argument parsing is needed, but
         * for good measure we will provide a simple
