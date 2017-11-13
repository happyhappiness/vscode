ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, f->r, APLOGNO(00776)
                "cache: CACHE filter was added in quick handler mode and "
                "will be ignored: %s", f->r->unparsed_uri);