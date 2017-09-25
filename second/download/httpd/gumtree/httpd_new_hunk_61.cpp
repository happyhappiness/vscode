                    cache->exp = exp;
                    cache->lastmod = lastmod;
                    cache->info = info;
                }
                APR_BRIGADE_FOREACH(e, in) {
                    apr_bucket *copy;
                    rv = apr_bucket_copy(e, &copy);
                    if (rv == APR_ENOTIMPL) {
                        const char *str;
                        apr_size_t len;

                        /* This takes care of uncopyable buckets. */
                        rv = apr_bucket_read(e, &str, &len, APR_BLOCK_READ);
                        if ((rv == APR_SUCCESS) &&
                            (cache->saved_size + len <=
                                        conf->max_streaming_buffer_size)) {
                            rv = apr_bucket_copy(e, &copy);
                        }

                        if ((rv != APR_SUCCESS) ||
                            (cache->saved_size + len >
                                        conf->max_streaming_buffer_size)){
                            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                                         "cache: not caching streamed response for "
                                         "%s because length %s", url,
                                          "> CacheMaxStreamingBuffer");

                            if (cache->saved_brigade != NULL) {
                                apr_brigade_destroy(cache->saved_brigade);
                                cache->saved_brigade = NULL;
                                cache->saved_size = 0;
                            }
                            ap_remove_output_filter(f);
                            return ap_pass_brigade(f->next, in);
                        }
                    }
                    APR_BRIGADE_INSERT_TAIL(cache->saved_brigade, copy);
                }
                cache->saved_size += size;
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                             "cache: Response length still unknown, setting "
                             "aside content for url: %s", url);
