         * unavailable.
         */
    } while (!PROXY_WORKER_IS_USABLE(worker) &&
             max_attempts > attempts++);

    if (DECLINED == access_status) {
        ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r, APLOGNO(01144)
                      "No protocol handler was valid for the URL %s. "
                      "If you are using a DSO version of mod_proxy, make sure "
                      "the proxy submodules are included in the configuration "
                      "using LoadModule.", r->uri);
        access_status = HTTP_INTERNAL_SERVER_ERROR;
        goto cleanup;
    }
cleanup:
    ap_proxy_post_request(worker, balancer, r, conf);

