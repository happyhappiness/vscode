        }
    }

    return status;
}

static void ssl_io_input_add_filter(ssl_filter_ctx_t *filter_ctx, conn_rec *c,
                                    SSL *ssl)
{
    bio_filter_in_ctx_t *inctx;

    inctx = apr_palloc(c->pool, sizeof(*inctx));
