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

