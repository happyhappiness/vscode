ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, t->r, 
                APLOGNO(02614) "mod_lua: Value for '%s' in table '%s' contains newline!",
                  key, t->n);