 
   if (h && h->attach_del)
   {
     dprint (3, (debugfile, "imap_copy_messages: Message contains attachments to be deleted\n"));
     return 1;
   }
-  
-  imap_fix_path (idata, mx.mbox, mbox, sizeof (mbox));
 
-  memset (&cmd, 0, sizeof (cmd));
-  mutt_buffer_addstr (&cmd, "UID COPY ");
+  imap_fix_path (idata, mx.mbox, mbox, sizeof (mbox));
+  if (!*mbox)
+    strfcpy (mbox, "INBOX", sizeof (mbox));
+  imap_munge_mbox_name (mmbox, sizeof (mmbox), mbox);
 
-  /* Null HEADER* means copy tagged messages */
-  if (!h)
+  /* loop in case of TRYCREATE */
+  do
   {
-    /* if any messages have attachments to delete, fall through to FETCH
-     * and APPEND. TODO: Copy what we can with COPY, fall through for the
-     * remainder. */
-    for (n = 0; n < ctx->msgcount; n++)
+    mutt_buffer_init (&sync_cmd);
+    mutt_buffer_init (&cmd);
+
+    /* Null HEADER* means copy tagged messages */
+    if (!h)
     {
-      if (ctx->hdrs[n]->tagged && ctx->hdrs[n]->attach_del)
+      /* if any messages have attachments to delete, fall through to FETCH
+       * and APPEND. TODO: Copy what we can with COPY, fall through for the
+       * remainder. */
+      for (n = 0; n < ctx->msgcount; n++)
       {
-	dprint (3, (debugfile, "imap_copy_messages: Message contains attachments to be deleted\n"));
-	return 1;
+        if (ctx->hdrs[n]->tagged && ctx->hdrs[n]->attach_del)
+        {
+          dprint (3, (debugfile, "imap_copy_messages: Message contains attachments to be deleted\n"));
+          return 1;
+        }
+
+        if (ctx->hdrs[n]->tagged && ctx->hdrs[n]->active &&
+            ctx->hdrs[n]->changed)
+        {
+          rc = imap_sync_message (idata, ctx->hdrs[n], &sync_cmd, &err_continue);
+          if (rc < 0)
+          {
+            dprint (1, (debugfile, "imap_copy_messages: could not sync\n"));
+            goto out;
+          }
+        }
       }
-    }
 
-    rc = imap_make_msg_set (idata, &cmd, M_TAG, 0);
-    if (!rc)
-    {
-      dprint (1, (debugfile, "imap_copy_messages: No messages tagged\n"));
-      goto fail;
+      rc = imap_exec_msgset (idata, "UID COPY", mmbox, M_TAG, 0, 0);
+      if (!rc)
+      {
+        dprint (1, (debugfile, "imap_copy_messages: No messages tagged\n"));
+        rc = -1;
+        goto out;
+      }
+      else if (rc < 0)
+      {
+        dprint (1, (debugfile, "could not queue copy\n"));
+        goto out;
+      }
+      else
+        mutt_message (_("Copying %d messages to %s..."), rc, mbox);
     }
-    mutt_message (_("Copying %d messages to %s..."), rc, mbox);
-  }
-  else
-  {
-    mutt_message (_("Copying message %d to %s..."), h->index+1, mbox);
-    snprintf (uid, sizeof (uid), "%u", HEADER_DATA (h)->uid);
-    mutt_buffer_addstr (&cmd, uid);
-  }
-
-  /* let's get it on */
-  mutt_buffer_addstr (&cmd, " ");
-  imap_munge_mbox_name (mmbox, sizeof (mmbox), mbox);
-  mutt_buffer_addstr (&cmd, mmbox);
-
-  rc = imap_exec (idata, cmd.data, IMAP_CMD_FAIL_OK);
-  if (rc == -2)
-  {
-    /* bail out if command failed for reasons other than nonexistent target */
-    if (ascii_strncasecmp (imap_get_qualifier (idata->cmd.buf), "[TRYCREATE]", 11))
+    else
     {
-      imap_error ("imap_copy_messages", idata->cmd.buf);
-      goto fail;
+      mutt_message (_("Copying message %d to %s..."), h->index+1, mbox);
+      mutt_buffer_printf (&cmd, "UID COPY %u %s", HEADER_DATA (h)->uid, mmbox);
+
+      if (h->active && h->changed)
+      {
+        rc = imap_sync_message (idata, h, &sync_cmd, &err_continue);
+        if (rc < 0)
+        {
+          dprint (1, (debugfile, "imap_copy_messages: could not sync\n"));
+          goto out;
+        }
+      }
+      if ((rc = imap_exec (idata, cmd.data, IMAP_CMD_QUEUE)) < 0)
+      {
+        dprint (1, (debugfile, "could not queue copy\n"));
+        goto out;
+      }
     }
-    dprint (2, (debugfile, "imap_copy_messages: server suggests TRYCREATE\n"));
-    snprintf (mmbox, sizeof (mmbox), _("Create %s?"), mbox);
-    if (option (OPTCONFIRMCREATE) && mutt_yesorno (mmbox, 1) < 1)
+
+    /* let's get it on */
+    rc = imap_exec (idata, NULL, IMAP_CMD_FAIL_OK);
+    if (rc == -2)
     {
-      mutt_clear_error ();
-      goto fail;
+      if (triedcreate)
+      {
+        dprint (1, (debugfile, "Already tried to create mailbox %s\n", mbox));
+        break;
+      }
+      /* bail out if command failed for reasons other than nonexistent target */
+      if (ascii_strncasecmp (imap_get_qualifier (idata->buf), "[TRYCREATE]", 11))
+        break;
+      dprint (3, (debugfile, "imap_copy_messages: server suggests TRYCREATE\n"));
+      snprintf (prompt, sizeof (prompt), _("Create %s?"), mbox);
+      if (option (OPTCONFIRMCREATE) && mutt_yesorno (prompt, 1) < 1)
+      {
+        mutt_clear_error ();
+        goto out;
+      }
+      if (imap_create_mailbox (idata, mbox) < 0)
+        break;
+      triedcreate = 1;
     }
-    if (imap_create_mailbox (idata, mbox) < 0)
-      goto fail;
-
-    /* try again */
-    rc = imap_exec (idata, cmd.data, 0);
   }
+  while (rc == -2);
+
   if (rc != 0)
   {
-    imap_error ("imap_copy_messages", idata->cmd.buf);
-    goto fail;
+    imap_error ("imap_copy_messages", idata->buf);
+    goto out;
   }
 
   /* cleanup */
   if (delete)
   {
     if (!h)
