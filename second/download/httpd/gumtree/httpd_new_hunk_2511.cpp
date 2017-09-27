                    if (etag) {
                        apr_table_set(r->headers_in, "If-None-Match", etag);
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

                /* ready to revalidate, pretend we were never here */
                return DECLINED;
            }

            /* Okay, this response looks okay.  Merge in our stuff and go. */
            cache_accept_headers(h, r, 0);

            cache->handle = h;
            return OK;
        }
        case DECLINED: {
            /* try again with next cache type */
