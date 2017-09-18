                if (apr_table_get(grpstatus, w)) {
                    return OK;
                }
            }
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Digest: access to %s failed, reason: unknown "
                          "require directive \"%s\"",
                          r->uri, reqs[x].requirement);
            return DECLINED;
        }
    }

    if (!method_restricted) {
        return OK;
    }

    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                  "Digest: access to %s failed, reason: user %s not "
                  "allowed access", r->uri, user);

    note_digest_auth_failure(r, conf,
        (digest_header_rec *) ap_get_module_config(r->request_config,
                                                   &auth_digest_module),
