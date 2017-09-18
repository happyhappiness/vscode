    }

    if (!(conf->auth_authoritative)) {
        return DECLINED;
    }

    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                  "access to %s failed, reason: user %s not allowed access",
                  r->uri, user);
        
    ap_note_basic_auth_failure(r);
    return HTTP_UNAUTHORIZED;
}
