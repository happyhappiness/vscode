ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, LOG_PREFIX
          "internal redirect to method '%s' and body mimetype '%s' for the "
                      "uri: %s", sent_method, sent_mimetype, r->uri);