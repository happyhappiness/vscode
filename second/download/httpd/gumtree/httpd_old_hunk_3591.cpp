                /* this cannot happen if end_token contains '>' */
                if (endp == NULL) {
                  return "end directive missing closing '>'";
                }

                warn_if_non_blank(
                    "non blank chars found after directive closing",
                    endp+1, config_file);

                macro_nesting--;
                if (!macro_nesting) {
                    if (any_nesting) {
                        ap_log_error(APLOG_MARK,
                                     APLOG_NOERRNO | APLOG_WARNING, 0, NULL,
                                     "bad cumulated nesting (%+d) in %s",
                                     any_nesting, where);
                    }
                    *plines = lines;
                    return NULL;
                }
