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

