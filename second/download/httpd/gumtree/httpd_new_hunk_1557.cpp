                }
            }

            zRC = deflate(&(ctx->stream), Z_NO_FLUSH);

            if (zRC != Z_OK) {
                return APR_EGENERAL;
            }
        }

        apr_bucket_delete(e);
    }

    apr_brigade_cleanup(bb);
    return APR_SUCCESS;
}

/* This is the deflate input filter (inflates).  */
static apr_status_t deflate_in_filter(ap_filter_t *f,
                                      apr_bucket_brigade *bb,
                                      ap_input_mode_t mode,
                                      apr_read_type_e block,
                                      apr_off_t readbytes)
