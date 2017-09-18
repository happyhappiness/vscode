                                            r, r->connection);

                return DECLINED;
            }
            /* else if non-conditional request */
            else {
                /* Temporarily hack this to work the way it had been. Its broken,
                 * but its broken the way it was before. I'm working on figuring
                 * out why the filter add in the conditional filter doesn't work. pjr
                 *
                 * info = &(cache->handle->cache_obj->info);
                 *
                 * Uncomment the above when the code in cache_conditional_filter_handle
                 * is properly fixed...  pjr
                 */
                
                /* fudge response into a conditional */
                if (info && info->etag) {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, 
                                 r->server,
                                 "cache: nonconditional - fudge conditional "
                                 "by etag");
