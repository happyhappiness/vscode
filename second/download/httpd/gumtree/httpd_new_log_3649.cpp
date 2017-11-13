ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r,
                  "uri: %s file: %s method: %d "
                  "imt: %s flags: %s%s%s %s->%s",
                  r->uri,
                  r->filename ? r->filename : "(none)",
                  r->method_number,
                  r->content_type ? r->content_type : "(unknown)",
                  r->main     ? "S" : "",    /* S if subrequest */
                  r->prev     ? "R" : "",    /* R if redirect */
                  r->proxyreq ? "P" : "",    /* P if proxy */
                  dc->charset_source, dc->charset_default);