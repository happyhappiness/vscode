                r->status = HTTP_BAD_REQUEST;
            }
            r->proto_num = HTTP_VERSION(1,0);
            r->protocol  = apr_pstrdup(r->pool, "HTTP/1.0");
            return 0;
        }
    } while ((len <= 0) && (--num_blank_lines >= 0));

    if (APLOGrtrace5(r)) {
        ap_log_rerror(APLOG_MARK, APLOG_TRACE5, 0, r,
                      "Request received from client: %s",
                      ap_escape_logitem(r->pool, r->the_request));
    }
