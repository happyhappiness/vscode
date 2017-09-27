                    }

                    if (lastmod) {
                        apr_table_set(r->headers_in, "If-Modified-Since",
                                      lastmod);
                    }
                    /*
                     * Do not do Range requests with our own conditionals: If
                     * we get 304 the Range does not matter and otherwise the
                     * entity changed and we want to have the complete entity
                     */
                    apr_table_unset(r->headers_in, "Range");
                }
                return DECLINED;
            }

            /* Okay, this response looks okay.  Merge in our stuff and go. */
            ap_cache_accept_headers(h, r, 0);

