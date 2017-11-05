ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "dropping filter '%s' in internal redirect from %s to %s",
                              f->frec->name, r->unparsed_uri, new_uri);