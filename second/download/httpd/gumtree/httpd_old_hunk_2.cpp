        else
            ret = HTTP_FORBIDDEN;
    }

    if (ret == HTTP_FORBIDDEN
        && (ap_satisfies(r) != SATISFY_ANY || !ap_some_auth_required(r))) {
        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
            "client denied by server configuration: %s",
            r->filename);
    }

    return ret;
}
