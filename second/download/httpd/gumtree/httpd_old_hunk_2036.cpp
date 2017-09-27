                    if (lastmod) {
                        apr_table_set(r->headers_in, "If-Modified-Since",
                                      lastmod);
                    }
                    cache->stale_handle = h;
                }

                return DECLINED;
            }

            /* Okay, this response looks okay.  Merge in our stuff and go. */
            ap_cache_accept_headers(h, r, 0);
