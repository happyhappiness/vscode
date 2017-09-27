         }
 
         zRC = inflateInit2(&ctx->stream, c->windowSize);
 
         if (zRC != Z_OK) {
             f->ctx = NULL;
+            inflateEnd(&ctx->stream);
             ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                           "unable to init Zlib: "
                           "inflateInit2 returned %d: URL %s",
                           zRC, r->uri);
             ap_remove_input_filter(f);
             return ap_get_brigade(f->next, bb, mode, block, readbytes);
