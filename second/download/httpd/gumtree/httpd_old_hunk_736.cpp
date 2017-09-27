
        /* XXX: probably a better way to determine this */
        if (SSL_total_renegotiations(filter_ctx->pssl)) {
            reason = "likely due to failed renegotiation";
        }

        ap_log_error(APLOG_MARK, APLOG_INFO, outctx->rc, c->base_server,
                     "failed to write %d of %d bytes (%s)",
                     len - (apr_size_t)res, len, reason);

        outctx->rc = APR_EGENERAL;
    }
    return outctx->rc;
}

