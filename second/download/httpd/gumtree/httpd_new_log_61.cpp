ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                                         "cache: not caching streamed response for "
                                         "%s because length %s", url,
                                          "> CacheMaxStreamingBuffer");