        else {
            if (apr_table_get(r->subprocess_env, &envar[1]) != NULL) {
                return DECLINED;
            }
        }
    }

    format = cls->format ? cls->format : default_format;

    strs = apr_palloc(r->pool, sizeof(char *) * (format->nelts));
    strl = apr_palloc(r->pool, sizeof(int) * (format->nelts));
    items = (log_format_item *) format->elts;
