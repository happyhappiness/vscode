                    }

                    if (lastmod) {
                        apr_table_set(r->headers_in, "If-Modified-Since",
                                      lastmod);
                    }
                    cache->stale_handle = h;
                }
                else {
                    int irv;

                    /*
                     * The copy isn't fresh enough, but we cannot revalidate.
                     * So it is the same case as if there had not been a cached
                     * entry at all. Thus delete the entry from cache.
                     */
                    irv = cache->provider->remove_url(h, r->pool);
                    if (irv != OK) {
                        ap_log_error(APLOG_MARK, APLOG_DEBUG, irv, r->server,
                                     "cache: attempt to remove url from cache unsuccessful.");
                    }
                }

                return DECLINED;
            }

            /* Okay, this response looks okay.  Merge in our stuff and go. */
            ap_cache_accept_headers(h, r, 0);

