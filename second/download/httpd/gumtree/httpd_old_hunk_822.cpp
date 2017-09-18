                    cache->exp = exp;
                    cache->lastmod = lastmod;
                    cache->info = info;
                }
                APR_BRIGADE_FOREACH(e, in) {
                    apr_bucket *copy;
                    apr_bucket_copy(e, &copy);
                    APR_BRIGADE_INSERT_TAIL(cache->saved_brigade, copy);
                }
                cache->saved_size += size;
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                             "cache: Response length still unknown, setting "
                             "aside content for url: %s", url);
