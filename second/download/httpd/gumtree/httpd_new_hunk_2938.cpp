                 || !strcasecmp(stringname, "Destination"))
        {
          value = ap_proxy_location_reverse_map(r, dconf, value);
        }

        ap_xlate_proto_from_ascii(value, strlen(value));
        ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r,
               "ajp_unmarshal_response: Header[%d] [%s] = [%s]",
                       i, stringname, value);

        apr_table_add(r->headers_out, stringname, value);

        /* Content-type needs an additional handling */
        if (strcasecmp(stringname, "Content-Type") == 0) {
             /* add corresponding filter */
            ap_set_content_type(r, apr_pstrdup(r->pool, value));
            ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r,
               "ajp_unmarshal_response: ap_set_content_type to '%s'", value);
        }
    }

    return APR_SUCCESS;
}

