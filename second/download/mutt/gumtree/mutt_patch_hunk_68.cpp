   mhs->flags[i] &= ~f;
   return mhs->flags[i];
 }
 
 #endif
 
-static void mh_read_token (char *t, int *first, int *last)
+static int mh_read_token (char *t, int *first, int *last)
 {
   char *p;
   if ((p = strchr (t, '-')))
   {
     *p++ = '\0';
-    *first = atoi (t);
-    *last  = atoi (p);
+    if (mutt_atoi (t, first) < 0 || mutt_atoi (p, last) < 0)
+      return -1;
   }
   else
-    *first = *last = atoi (t);
+  {
+    if (mutt_atoi (t, first) < 0)
+      return -1;
+    *last = *first;
+  }
+  return 0;
 }
 
-static void mh_read_sequences (struct mh_sequences *mhs, const char *path)
+static int mh_read_sequences (struct mh_sequences *mhs, const char *path)
 {
   FILE *fp;
   int line = 1;
   char *buff = NULL;
   char *t;
   size_t sz = 0;
-  
+
   short f;
-  int first, last;
+  int first, last, rc = 0;
 
   char pathname[_POSIX_PATH_MAX];
-  snprintf (pathname, sizeof (pathname),  "%s/.mh_sequences", path);
+  snprintf (pathname, sizeof (pathname), "%s/.mh_sequences", path);
 
   if (!(fp = fopen (pathname, "r")))
-    return;
+    return 0; /* yes, ask callers to silently ignore the error */
 
-  while ((buff = mutt_read_line (buff, &sz, fp, &line)))
+  while ((buff = mutt_read_line (buff, &sz, fp, &line, 0)))
   {
     if (!(t = strtok (buff, " \t:")))
       continue;
-    
+
     if (!mutt_strcmp (t, MhUnseen))
       f = MH_SEQ_UNSEEN;
     else if (!mutt_strcmp (t, MhFlagged))
       f = MH_SEQ_FLAGGED;
     else if (!mutt_strcmp (t, MhReplied))
       f = MH_SEQ_REPLIED;
-    else	/* unknown sequence */
+    else			/* unknown sequence */
       continue;
-    
+
     while ((t = strtok (NULL, " \t:")))
     {
-      mh_read_token (t, &first, &last);
+      if (mh_read_token (t, &first, &last) < 0)
+      {
+	mhs_free_sequences (mhs);
+	rc = -1;
+	goto out;
+      }
       for (; first <= last; first++)
 	mhs_set (mhs, first, f);
     }
   }
 
-  safe_free ((void **) &buff);
+  rc = 0;
+
+out:
+  FREE (&buff);
   safe_fclose (&fp);
+  return rc;
+}
+
+static inline mode_t mh_umask (CONTEXT* ctx)
+{
+  struct stat st;
+  struct mh_data* data = mh_data (ctx);
+
+  if (data && data->mh_umask)
+    return data->mh_umask;
+
+  if (stat (ctx->path, &st))
+  {
+    dprint (1, (debugfile, "stat failed on %s\n", ctx->path));
+    return 077;
+  }
+
+  return 0777 & ~st.st_mode;
+}
+
+/*
+ * Returns 1 if the .mh_sequences last modification time is more recent than the last visit to this mailbox
+ * Returns 0 if the modifcation time is older
+ * Returns -1 on error
+ */
+static int mh_sequences_changed(BUFFY *b)
+{
+  char path[_POSIX_PATH_MAX];
+  struct stat sb;
+
+  if ((snprintf(path, sizeof(path), "%s/.mh_sequences", b->path) < sizeof(path)) &&
+      (stat(path, &sb) == 0))
+    return (sb.st_mtime > b->last_visited);
+  return -1;
+}
+
+/*
+ * Returns 1 if the modification time on the message file is older than the last visit to this mailbox
+ * Returns 0 if the modtime is newer
+ * Returns -1 on error
+ */
+static int mh_already_notified(BUFFY *b, int msgno)
+{
+  char path[_POSIX_PATH_MAX];
+  struct stat sb;
+
+  if ((snprintf(path, sizeof(path), "%s/%d", b->path, msgno) < sizeof(path)) &&
+      (stat(path, &sb) == 0))
+    return (sb.st_mtime <= b->last_visited);
+  return -1;
 }
 
-int mh_buffy (const char *path)
+void mh_buffy(BUFFY *b)
 {
-  int i, r = 0;
+  int i;
   struct mh_sequences mhs;
+
+  b->new = 0;
+
+  /* when $mail_check_recent is set and the .mh_sequences file hasn't changed
+   * since the last mailbox visit, there is nothing to do */
+  if (option(OPTMAILCHECKRECENT) && mh_sequences_changed(b) <= 0)
+      return;
+
   memset (&mhs, 0, sizeof (mhs));
-  
-  mh_read_sequences (&mhs, path);
-  for (i = 0; !r && i <= mhs.max; i++)
+
+  if (mh_read_sequences (&mhs, b->path) < 0)
+    return;
+
+  /* Traverse the sequence from high to low in order to support
+   * $mail_check_recent.  Given that new messages are appended, this should
+   * also be faster when it is unset as well.
+   */
+  for (i = mhs.max; i > 0; i--)
+  {
     if (mhs_check (&mhs, i) & MH_SEQ_UNSEEN)
-      r = 1;
+    {
+      /* if the first unseen message we encounter was in the mailbox during the last visit, don't notify about it */
+      if (!option(OPTMAILCHECKRECENT) || mh_already_notified(b, i) == 0)
+	b->new = 1;
+      break;
+    }
+  }
   mhs_free_sequences (&mhs);
-  return r;
 }
 
-static int mh_mkstemp (CONTEXT *dest, FILE **fp, char **tgt)
+static int mh_mkstemp (CONTEXT * dest, FILE ** fp, char **tgt)
 {
   int fd;
   char path[_POSIX_PATH_MAX];
+  mode_t omask;
 
-  FOREVER 
+  omask = umask (mh_umask (dest));
+  FOREVER
   {
     snprintf (path, _POSIX_PATH_MAX, "%s/.mutt-%s-%d-%d",
 	      dest->path, NONULL (Hostname), (int) getpid (), Counter++);
-    if ((fd = open (path, O_WRONLY | O_EXCL | O_CREAT, 0600)) == -1)
+    if ((fd = open (path, O_WRONLY | O_EXCL | O_CREAT, 0666)) == -1)
     {
       if (errno != EEXIST)
       {
 	mutt_perror (path);
+	umask (omask);
 	return -1;
       }
     }
     else
     {
       *tgt = safe_strdup (path);
       break;
     }
   }
+  umask (omask);
 
   if ((*fp = fdopen (fd, "w")) == NULL)
   {
-    FREE (tgt);
+    FREE (tgt);		/* __FREE_CHECKED__ */
     close (fd);
     unlink (path);
     return (-1);
   }
-  
+
   return 0;
 }
 
-static void mhs_write_one_sequence (FILE *fp, struct mh_sequences *mhs,
+static void mhs_write_one_sequence (FILE * fp, struct mh_sequences *mhs,
 				    short f, const char *tag)
 {
   int i;
   int first, last;
   fprintf (fp, "%s:", tag);
-  
+
   first = -1;
-  last  = -1;
-  
+  last = -1;
+
   for (i = 0; i <= mhs->max; i++)
   {
     if ((mhs_check (mhs, i) & f))
     {
       if (first < 0)
 	first = i;
