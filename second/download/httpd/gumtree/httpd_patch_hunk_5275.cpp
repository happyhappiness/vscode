             else {
                 ctx->broken = 1;
                 ap_lua_release_state(L, ctx->spec, r);
                 ap_remove_output_filter(f);
                 apr_brigade_cleanup(pbbIn);
                 apr_brigade_cleanup(ctx->tmpBucket);
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                                    "lua: Error while executing filter: %s",
+                        lua_tostring(L, -1));
                 return HTTP_INTERNAL_SERVER_ERROR;
             }
         }
         /* If we've safely reached the end, do a final call to Lua to allow for any 
         finishing moves by the script, such as appending a tail. */
         if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(pbbIn))) {
