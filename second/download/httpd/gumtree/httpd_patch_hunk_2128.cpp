         /* uncomment this to see how the tree a built:
          *
          * DEBUG_DUMP_TREE(ctx, root);
          */
         CREATE_NODE(ctx, new);
 
-        was_unmatched = get_ptoken(ctx->dpool, &parse, &new->token);
+        was_unmatched = get_ptoken(ctx, &parse, &new->token,
+                         (current != NULL ? &current->token : NULL));
         if (!parse) {
             break;
         }
 
         DEBUG_DUMP_UNMATCHED(ctx, was_unmatched);
         DEBUG_DUMP_TOKEN(ctx, &new->token);
 
         if (!current) {
             switch (new->token.type) {
             case TOKEN_STRING:
             case TOKEN_NOT:
+            case TOKEN_ACCESS:
             case TOKEN_LBRACE:
                 root = current = new;
                 continue;
 
             default:
                 ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, error, expr,
