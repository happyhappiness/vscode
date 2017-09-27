            goto run_session;
        }
        /* done */
        ctx->engine = NULL;
    }

cleanup:
    if (!reconnected && ctx->engine && next_request(ctx, 1) == APR_SUCCESS) {
        /* Still more to do, tear down old conn and start over */
        if (ctx->p_conn) {
            ctx->p_conn->close = 1;
            /*only in trunk so far */
            /*proxy_run_detach_backend(r, ctx->p_conn);*/
            ap_proxy_release_connection(ctx->proxy_func, ctx->p_conn, ctx->server);
            ctx->p_conn = NULL;
        }
        reconnected = 1; /* we do this only once, then fail */
        goto run_connect;
    }
    
    if (ctx->p_conn) {
        if (status != APR_SUCCESS) {
            /* close socket when errors happened or session shut down (EOF) */
            ctx->p_conn->close = 1;
        }
        /*only in trunk so far */
        /*proxy_run_detach_backend(ctx->rbase, ctx->p_conn);*/
        ap_proxy_release_connection(ctx->proxy_func, ctx->p_conn, ctx->server);
        ctx->p_conn = NULL;
    }

    ap_set_module_config(ctx->owner->conn_config, &proxy_http2_module, NULL);
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, ctx->owner, 
                  APLOGNO(03377) "leaving handler");
    return ctx->r_status;
}

