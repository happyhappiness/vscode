
        /* XXX: probably a better way to determine this */
        if (SSL_total_renegotiations(ctx->pssl)) {
            reason = "likely due to failed renegotiation";
        }

        ssl_log(c->base_server, SSL_LOG_ERROR,
                "failed to write %d of %d bytes (%s)",
                n > 0 ? len - n : len, len, reason);

        return APR_EINVAL;
    }

