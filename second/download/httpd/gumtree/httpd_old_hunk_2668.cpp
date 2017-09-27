                       ctx->stream.next_in, copy_size);
                /* Saved copy_size bytes */
                ctx->stream.avail_in -= copy_size;
                ctx->validation_buffer_length += copy_size;
            }
            if (ctx->stream.avail_in) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "Zlib: %d bytes of garbage at the end of "
                              "compressed stream.", ctx->stream.avail_in);
                /*
                 * There is nothing worth consuming for zlib left, because it is
                 * either garbage data or the data has been copied to the
                 * validation buffer (processing validation data is no business
