 
         /* try to match end_seq at current pos. */
         case PARSE_TAIL:
         case PARSE_TAIL_SEQ:
             index = find_tail(ctx, data, len);
 
-            switch (ctx->state) {
+            switch (intern->state) {
             case PARSE_EXECUTE:  /* full match */
                 apr_bucket_split(b, index);
                 newb = APR_BUCKET_NEXT(b);
                 apr_bucket_delete(b);
                 b = newb;
                 break;
 
             case PARSE_ARG:      /* no match */
                 /* PARSE_ARG must reparse at the beginning */
-                APR_BRIGADE_PREPEND(bb, ctx->tmp_bb);
+                APR_BRIGADE_PREPEND(bb, intern->tmp_bb);
                 b = APR_BRIGADE_FIRST(bb);
                 break;
 
             default:             /* partial match */
                 newb = APR_BUCKET_NEXT(b);
                 APR_BUCKET_REMOVE(b);
-                APR_BRIGADE_INSERT_TAIL(ctx->tmp_bb, b);
+                APR_BRIGADE_INSERT_TAIL(intern->tmp_bb, b);
                 b = newb;
                 break;
             }
 
             break;
 
         /* now execute the parsed directive, cleanup the space and
          * start again with PARSE_PRE_HEAD
          */
         case PARSE_EXECUTE:
             /* if there was an error, it was already logged; just stop here */
-            if (ctx->error) {
-                if (ctx->ctx->flags & FLAG_PRINTING) {
-                    SSI_CREATE_ERROR_BUCKET(ctx->ctx, f, pass_bb);
-                    ctx->error = 0;
+            if (intern->error) {
+                if (ctx->flags & SSI_FLAG_PRINTING) {
+                    SSI_CREATE_ERROR_BUCKET(ctx, f, pass_bb);
+                    intern->error = 0;
                 }
             }
             else {
                 include_handler_fn_t *handle_func;
 
                 handle_func =
-                    (include_handler_fn_t *) apr_hash_get(include_hash,
-                                                    ctx->directive,
-                                                    ctx->ctx->directive_length);
-                if (handle_func) {
-                    apr_bucket *dummy;
-                    char *tag;
-                    apr_size_t tag_len = 0;
-                    ssi_arg_item_t *carg = ctx->argv;
-
-                    /* legacy wrapper code */
-                    while (carg) {
-                        /* +1 \0 byte (either after tag or value)
-                         * +1 =  byte (before value)
-                         */
-                        tag_len += (carg->name  ? carg->name_len      : 0) +
-                                   (carg->value ? carg->value_len + 1 : 0) + 1;
-                        carg = carg->next;
-                    }
-
-                    tag = ctx->ctx->combined_tag = ctx->ctx->curr_tag_pos =
-                        apr_palloc(ctx->dpool, tag_len);
-
-                    carg = ctx->argv;
-                    while (carg) {
-                        if (carg->name) {
-                            memcpy(tag, carg->name, carg->name_len);
-                            tag += carg->name_len;
-                        }
-                        if (carg->value) {
-                            *tag++ = '=';
-                            memcpy(tag, carg->value, carg->value_len);
-                            tag += carg->value_len;
-                        }
-                        *tag++ = '\0';
-                        carg = carg->next;
-                    }
-                    ctx->ctx->tag_length = tag_len;
-
-                    /* create dummy buckets for backards compat */
-                    ctx->ctx->head_start_bucket =
-                        apr_bucket_pool_create(apr_pmemdup(ctx->ctx->pool,
-                                                           ctx->ctx->start_seq,
-                                                       ctx->ctx->start_seq_len),
-                                               ctx->ctx->start_seq_len,
-                                               ctx->ctx->pool,
-                                               f->c->bucket_alloc);
-                    APR_BRIGADE_INSERT_TAIL(ctx->ctx->ssi_tag_brigade,
-                                            ctx->ctx->head_start_bucket);
-                    ctx->ctx->tag_start_bucket =
-                        apr_bucket_pool_create(apr_pmemdup(ctx->ctx->pool,
-                                                         ctx->ctx->combined_tag,
-                                                         ctx->ctx->tag_length),
-                                               ctx->ctx->tag_length,
-                                               ctx->ctx->pool,
-                                               f->c->bucket_alloc);
-                    APR_BRIGADE_INSERT_TAIL(ctx->ctx->ssi_tag_brigade,
-                                            ctx->ctx->tag_start_bucket);
-                    ctx->ctx->tail_start_bucket =
-                        apr_bucket_pool_create(apr_pmemdup(ctx->ctx->pool,
-                                                           ctx->ctx->end_seq,
-                                                           ctx->end_seq_len),
-                                               ctx->end_seq_len,
-                                               ctx->ctx->pool,
-                                               f->c->bucket_alloc);
-                    APR_BRIGADE_INSERT_TAIL(ctx->ctx->ssi_tag_brigade,
-                                            ctx->ctx->tail_start_bucket);
-
-                    rv = handle_func(ctx->ctx, &bb, r, f, b, &dummy);
+                    (include_handler_fn_t *)apr_hash_get(include_handlers, intern->directive,
+                                                         intern->directive_len);
 
-                    apr_brigade_cleanup(ctx->ctx->ssi_tag_brigade);
-
-                    if (rv != 0 && rv != 1 && rv != -1) {
+                if (handle_func) {
+                    DEBUG_INIT(ctx, f, pass_bb);
+                    rv = handle_func(ctx, f, pass_bb);
+                    if (rv != APR_SUCCESS) {
                         apr_brigade_destroy(pass_bb);
                         return rv;
                     }
-
-                    if (dummy) {
-                        apr_bucket_brigade *remain;
-
-                        remain = apr_brigade_split(bb, b);
-                        APR_BRIGADE_CONCAT(pass_bb, bb);
-                        bb = remain;
-                    }
                 }
                 else {
                     ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                   "unknown directive \"%s\" in parsed doc %s",
-                                  apr_pstrmemdup(r->pool, ctx->directive,
-                                                 ctx->ctx->directive_length),
+                                  apr_pstrmemdup(r->pool, intern->directive,
+                                                 intern->directive_len),
                                                  r->filename);
-                    if (ctx->ctx->flags & FLAG_PRINTING) {
-                        SSI_CREATE_ERROR_BUCKET(ctx->ctx, f, pass_bb);
+                    if (ctx->flags & SSI_FLAG_PRINTING) {
+                        SSI_CREATE_ERROR_BUCKET(ctx, f, pass_bb);
                     }
                 }
             }
 
             /* cleanup */
             apr_pool_clear(ctx->dpool);
-            apr_brigade_cleanup(ctx->tmp_bb);
+            apr_brigade_cleanup(intern->tmp_bb);
 
             /* Oooof. Done here, start next round */
-            ctx->state = PARSE_PRE_HEAD;
+            intern->state = PARSE_PRE_HEAD;
             break;
-        }
 
-    } /* while (brigade) */
+        } /* switch(ctx->state) */
+
+    } /* while(brigade) */
 
     /* End of stream. Final cleanup */
-    if (ctx->seen_eos) {
-        if (PARSE_HEAD == ctx->state) {
-            if (ctx->ctx->flags & FLAG_PRINTING) {
-                char *to_release = apr_palloc(ctx->ctx->pool,
-                                              ctx->ctx->parse_pos);
+    if (intern->seen_eos) {
+        if (PARSE_HEAD == intern->state) {
+            if (ctx->flags & SSI_FLAG_PRINTING) {
+                char *to_release = apr_palloc(ctx->pool, intern->parse_pos);
 
-                memcpy(to_release, ctx->ctx->start_seq, ctx->ctx->parse_pos);
+                memcpy(to_release, intern->start_seq, intern->parse_pos);
                 APR_BRIGADE_INSERT_TAIL(pass_bb,
                                         apr_bucket_pool_create(to_release,
-                                        ctx->ctx->parse_pos, ctx->ctx->pool,
+                                        intern->parse_pos, ctx->pool,
                                         f->c->bucket_alloc));
             }
         }
-        else if (PARSE_PRE_HEAD != ctx->state) {
+        else if (PARSE_PRE_HEAD != intern->state) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                           "SSI directive was not properly finished at the end "
                           "of parsed document %s", r->filename);
-            if (ctx->ctx->flags & FLAG_PRINTING) {
-                SSI_CREATE_ERROR_BUCKET(ctx->ctx, f, pass_bb);
+            if (ctx->flags & SSI_FLAG_PRINTING) {
+                SSI_CREATE_ERROR_BUCKET(ctx, f, pass_bb);
             }
         }
 
-        if (!(ctx->ctx->flags & FLAG_PRINTING)) {
+        if (!(ctx->flags & SSI_FLAG_PRINTING)) {
             ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                           "missing closing endif directive in parsed document"
                           " %s", r->filename);
         }
 
         /* cleanup our temporary memory */
-        apr_brigade_destroy(ctx->tmp_bb);
+        apr_brigade_destroy(intern->tmp_bb);
         apr_pool_destroy(ctx->dpool);
 
         /* don't forget to finally insert the EOS bucket */
         APR_BRIGADE_INSERT_TAIL(pass_bb, b);
     }
 
     /* if something's left over, pass it along */
     if (!APR_BRIGADE_EMPTY(pass_bb)) {
         rv = ap_pass_brigade(f->next, pass_bb);
     }
     else {
         rv = APR_SUCCESS;
+        apr_brigade_destroy(pass_bb);
     }
-
-    apr_brigade_destroy(pass_bb);
     return rv;
 }
 
-static void *create_includes_dir_config(apr_pool_t *p, char *dummy)
-{
-    include_dir_config *result =
-        (include_dir_config *)apr_palloc(p, sizeof(include_dir_config));
-    enum xbithack *xbh = (enum xbithack *) apr_palloc(p, sizeof(enum xbithack));
-    *xbh = DEFAULT_XBITHACK;
-    result->default_error_msg = DEFAULT_ERROR_MSG;
-    result->default_time_fmt = DEFAULT_TIME_FORMAT;
-    result->xbithack = xbh;
-    return result;
-}
-
-static void *create_includes_server_config(apr_pool_t*p, server_rec *server)
-{
-    include_server_config *result =
-        (include_server_config *)apr_palloc(p, sizeof(include_server_config));
-    result->default_end_tag = ENDING_SEQUENCE;
-    result->default_start_tag =STARTING_SEQUENCE;
-    result->start_tag_len = sizeof(STARTING_SEQUENCE)-1;
-    /* compile the pattern used by find_start_sequence */
-    bndm_compile(&result->start_seq_pat, result->default_start_tag, 
-                 result->start_tag_len); 
-
-    result->undefinedEcho = apr_pstrdup(p,"(none)");
-    result->undefinedEchoLen = strlen( result->undefinedEcho);
-    return result; 
-}
-static const char *set_xbithack(cmd_parms *cmd, void *xbp, const char *arg)
-{
-    include_dir_config *conf = (include_dir_config *)xbp;
-
-    if (!strcasecmp(arg, "off")) {
-        *conf->xbithack = xbithack_off;
-    }
-    else if (!strcasecmp(arg, "on")) {
-        *conf->xbithack = xbithack_on;
-    }
-    else if (!strcasecmp(arg, "full")) {
-        *conf->xbithack = xbithack_full;
-    }
-    else {
-        return "XBitHack must be set to Off, On, or Full";
-    }
 
-    return NULL;
-}
+/*
+ * +-------------------------------------------------------+
+ * |                                                       |
+ * |                     Runtime Hooks
+ * |                                                       |
+ * +-------------------------------------------------------+
+ */
 
 static int includes_setup(ap_filter_t *f)
 {
-    include_dir_config *conf = 
-               (include_dir_config *)ap_get_module_config(f->r->per_dir_config,
-                                                          &include_module);
+    include_dir_config *conf = ap_get_module_config(f->r->per_dir_config,
+                                                    &include_module);
 
     /* When our xbithack value isn't set to full or our platform isn't
      * providing group-level protection bits or our group-level bits do not
      * have group-execite on, we will set the no_local_copy value to 1 so
      * that we will not send 304s.
      */
-    if ((*conf->xbithack != xbithack_full)
+    if ((conf->xbithack != XBITHACK_FULL)
         || !(f->r->finfo.valid & APR_FINFO_GPROT)
         || !(f->r->finfo.protection & APR_GEXECUTE)) {
         f->r->no_local_copy = 1;
     }
 
     /* Don't allow ETag headers to be generated - see RFC2616 - 13.3.4.
