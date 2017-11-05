static apr_status_t ajp_unmarshal_response(ajp_msg_t *msg,
                                           request_rec *r,
                                           proxy_dir_conf *dconf)
{
    apr_uint16_t status;
    apr_status_t rc;
    const char *ptr;
    apr_uint16_t  num_headers;
    int i;

    rc = ajp_msg_get_uint16(msg, &status);

    if (rc != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                "ajp_unmarshal_response: Null status");
        return rc;
    }
    r->status = status;

    rc = ajp_msg_get_string(msg, &ptr);
    if (rc == APR_SUCCESS) {
#if APR_CHARSET_EBCDIC /* copy only if we have to */
        ptr = apr_pstrdup(r->pool, ptr);
        ap_xlate_proto_from_ascii(ptr, strlen(ptr));
#endif
        r->status_line =  apr_psprintf(r->pool, "%d %s", status, ptr);
    } else {
        r->status_line = NULL;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
           "ajp_unmarshal_response: status = %d", status);

    rc = ajp_msg_get_uint16(msg, &num_headers);
    if (rc == APR_SUCCESS) {
        apr_table_t *save_table;

        /* First, tuck away all already existing cookies */
        /*
         * Could optimize here, but just in case we want to
         * also save other headers, keep this logic.
         */
        save_table = apr_table_make(r->pool, num_headers + 2);
        apr_table_do(addit_dammit, save_table, r->headers_out,
                     "Set-Cookie", NULL);
        r->headers_out = save_table;
    } else {
        r->headers_out = NULL;
        num_headers = 0;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
           "ajp_unmarshal_response: Number of headers is = %d",
           num_headers);

    for(i = 0 ; i < (int) num_headers ; i++) {
        apr_uint16_t name;
        const char *stringname;
        const char *value;
        rc  = ajp_msg_peek_uint16(msg, &name);
        if (rc != APR_SUCCESS) {
            return rc;
        }

        if ((name & 0XFF00) == 0XA000) {
            ajp_msg_get_uint16(msg, &name);
            stringname = long_res_header_for_sc(name);
            if (stringname == NULL) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                       "ajp_unmarshal_response: "
                       "No such sc (%08x)",
                       name);
                return AJP_EBAD_HEADER;
            }
        } else {
            name = 0;
            rc = ajp_msg_get_string(msg, &stringname);
            if (rc != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                       "ajp_unmarshal_response: "
                       "Null header name");
                return rc;
            }
            ap_xlate_proto_from_ascii(stringname, strlen(stringname));
        }

        rc = ajp_msg_get_string(msg, &value);
        if (rc != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                   "ajp_unmarshal_response: "
                   "Null header value");
            return rc;
        }

        /* Set-Cookie need additional processing */
        if (!strcasecmp(stringname, "Set-Cookie")) {
            value = ap_proxy_cookie_reverse_map(r, dconf, value);
        }
        /* Location, Content-Location, URI and Destination need additional
         * processing */
        else if (!strcasecmp(stringname, "Location")
                 || !strcasecmp(stringname, "Content-Location")
                 || !strcasecmp(stringname, "URI")
                 || !strcasecmp(stringname, "Destination"))
        {
          value = ap_proxy_location_reverse_map(r, dconf, value);
        }

        ap_xlate_proto_from_ascii(value, strlen(value));
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
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

    return APR_SUCCESS;
}