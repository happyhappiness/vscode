        /* Add session info to env. */
        apr_table_setn(r->subprocess_env,
                       "BALANCER_SESSION_STICKY", sticky);
        apr_table_setn(r->subprocess_env,
                       "BALANCER_SESSION_ROUTE", route);
    }
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01172)
                  "%s: worker (%s) rewritten to %s",
                  (*balancer)->s->name, (*worker)->s->name, *url);

    return access_status;
}

static int proxy_balancer_post_request(proxy_worker *worker,
                                       proxy_balancer *balancer,
