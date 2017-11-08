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
        r->status_line =  apr_psprintf(r->pool, "%d %s", status, ptr);
#if defined(AS400) || defined(_OSD_POSIX)
        ap_xlate_proto_from_ascii(r->status_line, strlen(r->status_line));
#endif
    } else {
        r->status_line = NULL;
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
           "ajp_unmarshal_response: status = %d", status);

    rc = ajp_msg_get_uint16(msg, &num_headers);
    if (rc == APR_SUCCESS) {
        r->headers_out = apr_table_make(r->pool, num_headers);
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
#if defined(AS400) || defined(_OSD_POSIX)
            ap_xlate_proto_from_ascii(stringname, strlen(stringname));
#endif
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

#if defined(AS400) || defined(_OSD_POSIX)
        ap_xlate_proto_from_ascii(value, strlen(value));
#endif
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
               "ajp_unmarshal_response: Header[%d] [%s] = [%s]",
                       i, stringname, value);

        apr_table_add(r->headers_out, stringname, value);

        /* Content-type needs an additional handling */
        if (memcmp(stringname, "Content-Type", 12) == 0) {
             /* add corresponding filter */
            ap_set_content_type(r, apr_pstrdup(r->pool, value));
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
               "ajp_unmarshal_response: ap_set_content_type done");
        }
    }

    return APR_SUCCESS;
}