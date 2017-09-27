            value = "1";
        }
        ap_unescape_url(key);
        ap_unescape_url(value);
        apr_table_set(parms, key, value);
        /*
         ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03230)
         "Found query arg: %s = %s", key, value);
         */
        key = apr_strtok(NULL, "&", &strtok_state);
    }
}

