
                    if (writetty) {
                        apr_file_printf(writetty, "Apache:mod_ssl:Error: Pass phrase incorrect.\n");
                        apr_file_printf(writetty, "**Stopped\n");
                    }
                }
                ssl_die();
            }

            /* If a cached private key was found, nothing more to do
             * here; loop through to the next configured cert for this
             * vhost. */
            if (using_cache)
