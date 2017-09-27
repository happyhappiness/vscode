             apr_status_t rv;
 
             /* flush the remaining data from the zlib buffers */
             zRC = flush_libz_buffer(ctx, c, f->c->bucket_alloc, deflate,
                                     Z_SYNC_FLUSH, NO_UPDATE_CRC);
             if (zRC != Z_OK) {
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01385)
+                              "Zlib error %d flushing zlib output buffer (%s)",
+                              zRC, ctx->stream.msg);
                 return APR_EGENERAL;
             }
 
             /* Remove flush bucket from old brigade anf insert into the new. */
             APR_BUCKET_REMOVE(e);
             APR_BRIGADE_INSERT_TAIL(ctx->bb, e);
