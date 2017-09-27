                }
            }

            zRC = deflate(&(ctx->stream), Z_NO_FLUSH);

            if (zRC != Z_OK) {
                return APR_EGENERAL;
            }
        }

        apr_bucket_delete(e);
    }
