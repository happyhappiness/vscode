ap_log_rerror(APLOG_MARK, APLOG_WARNING, rv, f->r, APLOGNO(00766)
                        "cache: Cache provider's store_body returned an "
                        "empty brigade, but didn't consume all of the "
                        "input brigade, standing down to prevent a spin");