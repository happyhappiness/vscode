   if (mbox_lock_mailbox (ctx, 0, 1) == -1)
   {
     mutt_unblock_signals ();
     return (-1);
   }
 
-  if (ctx->magic == M_MBOX)
+  if (ctx->magic == MUTT_MBOX)
     rc = mbox_parse_mailbox (ctx);
-  else if (ctx->magic == M_MMDF)
+  else if (ctx->magic == MUTT_MMDF)
     rc = mmdf_parse_mailbox (ctx);
   else
     rc = -1;
 
   mbox_unlock_mailbox (ctx);
   mutt_unblock_signals ();
   return (rc);
 }
 
+static int mbox_open_mailbox_append (CONTEXT *ctx, int flags)
+{
+  ctx->fp = safe_fopen (ctx->path, flags & MUTT_NEWFOLDER ? "w" : "a");
+  if (!ctx->fp)
+  {
+    mutt_perror (ctx->path);
+    return -1;
+  }
+
+  if (mbox_lock_mailbox (ctx, 1, 1) != 0)
+  {
+    mutt_error (_("Couldn't lock %s\n"), ctx->path);
+    safe_fclose (&ctx->fp);
+    return -1;
+  }
+
+  fseek (ctx->fp, 0, 2);
+
+  return 0;
+}
+
+static int mbox_close_mailbox (CONTEXT *ctx)
+{
+  return 0;
+}
+
+static int mbox_open_message (CONTEXT *ctx,  MESSAGE *msg, int msgno)
+{
+  msg->fp = ctx->fp;
+
+  return 0;
+}
+
+static int mbox_close_message (CONTEXT *ctx, MESSAGE *msg)
+{
+  msg->fp = NULL;
+
+  return 0;
+}
+
+static int mbox_commit_message (CONTEXT *ctx, MESSAGE *msg)
+{
+  if (fputc ('\n', msg->fp) == EOF)
+    return -1;
+
+  if ((fflush (msg->fp) == EOF) ||
+      (fsync (fileno (msg->fp)) == -1))
+  {
+    mutt_perror _("Can't write message");
+    return -1;
+  }
+
+  return 0;
+}
+
+static int mmdf_commit_message (CONTEXT *ctx, MESSAGE *msg)
+{
+  if (fputs (MMDF_SEP, msg->fp) == EOF)
+    return -1;
+
+  if ((fflush (msg->fp) == EOF) ||
+      (fsync (fileno (msg->fp)) == -1))
+  {
+    mutt_perror _("Can't write message");
+    return -1;
+  }
+
+  return 0;
+}
+
+static int mbox_open_new_message (MESSAGE *msg, CONTEXT *dest, HEADER *hdr)
+{
+  msg->fp = dest->fp;
+  return 0;
+}
+
 /* return 1 if address lists are strictly identical */
 static int strict_addrcmp (const ADDRESS *a, const ADDRESS *b)
 {
   while (a && b)
   {
     if (mutt_strcmp (a->mailbox, b->mailbox) ||
