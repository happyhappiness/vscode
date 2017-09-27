ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r, APLOGNO(00777)
                "cache: CACHE filter was added twice, or was added where "
                "the cache has been bypassed and will be ignored: %s",
                f->r->unparsed_uri);