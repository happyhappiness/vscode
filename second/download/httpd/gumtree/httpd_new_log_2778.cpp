ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rr->status, r, 
                              "mod_include: The tested "
                              "subrequest -A \"%s\" returned an error code.",
                              current->right->token.value);