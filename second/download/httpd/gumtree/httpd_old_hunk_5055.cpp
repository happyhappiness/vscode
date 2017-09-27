                    return APR_EGENERAL;
                }

                inflateEnd(&ctx->stream);

                ctx->done = 1;
            }

        }
        apr_brigade_cleanup(ctx->bb);
    }

