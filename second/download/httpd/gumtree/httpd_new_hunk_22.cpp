
    if (!(t = ap_auth_type(r)) || strcasecmp(t, "Digest")) {
        return DECLINED;
    }

    if (!ap_auth_name(r)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Digest: need AuthName: %s", r->uri);
        return HTTP_INTERNAL_SERVER_ERROR;
    }


    /* get the client response and mark */
