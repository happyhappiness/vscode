ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Digest: access to %s failed, reason: unknown "
                          "require directive \"%s\"",
                          r->uri, reqs[x].requirement);