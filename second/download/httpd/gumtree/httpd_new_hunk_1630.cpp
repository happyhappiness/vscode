               "ajp_unmarshal_response: Header[%d] [%s] = [%s]",
                       i, stringname, value);

        apr_table_add(r->headers_out, stringname, value);

        /* Content-type needs an additional handling */
        if (strcasecmp(stringname, "Content-Type") == 0) {
             /* add corresponding filter */
            ap_set_content_type(r, apr_pstrdup(r->pool, value));
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
               "ajp_unmarshal_response: ap_set_content_type done");
        }
    }
