                          "%s: Unlock failed for balancer_handler",
                          balancer->s->name);
        }
    }

    if (r->args && (r->method_number == M_GET)) {
        const char *allowed[] = { "w", "b", "nonce", "xml", NULL };
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01191) "parsing r->args");

        push2table(r->args, params, allowed, r->pool);
    }
    if (r->method_number == M_POST) {
        apr_bucket_brigade *ib;
