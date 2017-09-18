            }
        }
        else if (!strcmp(tag, "done")) {
            return 0;
        }
        else {
            ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                        "unknown parameter \"%s\" to tag echo in %s",
                        tag, r->filename);
            ap_rputs(error, r);
        }
    }
}
