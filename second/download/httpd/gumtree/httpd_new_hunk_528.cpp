                }
            }
            apr_pool_clear(ctx->deferred_write_pool);  
        }

        if (rv != APR_SUCCESS) {
            ap_log_cerror(APLOG_MARK, APLOG_INFO, rv, c,
                          "core_output_filter: writing data to the network");

            if (more)
                apr_brigade_destroy(more);

            /* No need to check for SUCCESS, we did that above. */
            if (!APR_STATUS_IS_EAGAIN(rv)) {
