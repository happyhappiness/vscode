        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01173)
                      "%s: Lock failed for post_request",
                      balancer->s->name);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    if (!apr_is_empty_array(balancer->errstatuses)
        && !(worker->s->status & PROXY_WORKER_IGNORE_ERRORS)) {
        int i;
        for (i = 0; i < balancer->errstatuses->nelts; i++) {
            int val = ((int *)balancer->errstatuses->elts)[i];
            if (r->status == val) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01174)
                              "%s: Forcing worker (%s) into error state "
