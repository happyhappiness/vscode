cache_run_cache_status(cache->handle, r, r->headers_out,
                    AP_CACHE_REVALIDATE,
                    "conditional cache hit: entity refresh failed");