       mhs_set (&mhs, i, MH_SEQ_REPLIED);
       replied++;
     }
   }
 
   /* write out the new sequences */
-  if (unseen)  mhs_write_one_sequence (nfp, &mhs, MH_SEQ_UNSEEN, NONULL (MhUnseen));
-  if (flagged) mhs_write_one_sequence (nfp, &mhs, MH_SEQ_FLAGGED, NONULL (MhFlagged));
-  if (replied) mhs_write_one_sequence (nfp, &mhs, MH_SEQ_REPLIED, NONULL (MhReplied));
+  if (unseen)
+    mhs_write_one_sequence (nfp, &mhs, MH_SEQ_UNSEEN, NONULL (MhUnseen));
+  if (flagged)
+    mhs_write_one_sequence (nfp, &mhs, MH_SEQ_FLAGGED, NONULL (MhFlagged));
+  if (replied)
+    mhs_write_one_sequence (nfp, &mhs, MH_SEQ_REPLIED, NONULL (MhReplied));
 
   mhs_free_sequences (&mhs);
 
-  
+
   /* try to commit the changes - no guarantee here */
   safe_fclose (&nfp);
-  
+
   unlink (sequences);
   if (safe_rename (tmpfname, sequences) != 0)
   {
     /* report an error? */
     unlink (tmpfname);
   }
-  
-  safe_free ((void **) &tmpfname);
+
+  FREE (&tmpfname);
 }
 
-static void mh_sequences_add_one (CONTEXT *ctx, int n, short unseen, short flagged, short replied)
+static void mh_sequences_add_one (CONTEXT * ctx, int n, short unseen,
+				  short flagged, short replied)
 {
   short unseen_done = 0;
   short flagged_done = 0;
   short replied_done = 0;
-  
+
   FILE *ofp = NULL, *nfp = NULL;
- 
+
   char *tmpfname;
   char sequences[_POSIX_PATH_MAX];
 
   char seq_unseen[STRING];
   char seq_replied[STRING];
   char seq_flagged[STRING];
-  
+
   char *buff = NULL;
   int line;
   size_t sz;
-  
+
   if (mh_mkstemp (ctx, &nfp, &tmpfname) == -1)
     return;
 
   snprintf (seq_unseen, sizeof (seq_unseen), "%s:", NONULL (MhUnseen));
   snprintf (seq_replied, sizeof (seq_replied), "%s:", NONULL (MhReplied));
   snprintf (seq_flagged, sizeof (seq_flagged), "%s:", NONULL (MhFlagged));
-  
+
   snprintf (sequences, sizeof (sequences), "%s/.mh_sequences", ctx->path);
   if ((ofp = fopen (sequences, "r")))
   {
-    while ((buff = mutt_read_line (buff, &sz, ofp, &line)))
+    while ((buff = mutt_read_line (buff, &sz, ofp, &line, 0)))
     {
       if (unseen && !strncmp (buff, seq_unseen, mutt_strlen (seq_unseen)))
       {
 	fprintf (nfp, "%s %d\n", buff, n);
 	unseen_done = 1;
       }
-      else if (flagged && !strncmp (buff, seq_flagged, mutt_strlen (seq_flagged)))
+      else if (flagged
+	       && !strncmp (buff, seq_flagged, mutt_strlen (seq_flagged)))
       {
 	fprintf (nfp, "%s %d\n", buff, n);
 	flagged_done = 1;
       }
-      else if (replied && !strncmp (buff, seq_replied, mutt_strlen (seq_replied)))
+      else if (replied
+	       && !strncmp (buff, seq_replied, mutt_strlen (seq_replied)))
       {
 	fprintf (nfp, "%s %d\n", buff, n);
 	replied_done = 1;
       }
       else
 	fprintf (nfp, "%s\n", buff);
     }
   }
   safe_fclose (&ofp);
-  safe_free ((void **) &buff);
-  
-  if (!unseen_done  && unseen)   fprintf (nfp, "%s: %d\n", NONULL (MhUnseen), n);
-  if (!flagged_done && flagged)  fprintf (nfp, "%s: %d\n", NONULL (MhFlagged), n);
-  if (!replied_done && replied)  fprintf (nfp, "%s: %d\n", NONULL (MhReplied), n);
-  
+  FREE (&buff);
+
+  if (!unseen_done && unseen)
+    fprintf (nfp, "%s: %d\n", NONULL (MhUnseen), n);
+  if (!flagged_done && flagged)
+    fprintf (nfp, "%s: %d\n", NONULL (MhFlagged), n);
+  if (!replied_done && replied)
+    fprintf (nfp, "%s: %d\n", NONULL (MhReplied), n);
+
   safe_fclose (&nfp);
-  
+
   unlink (sequences);
   if (safe_rename (tmpfname, sequences) != 0)
     unlink (tmpfname);
-  
-  safe_free ((void **) &tmpfname);
+
+  FREE (&tmpfname);
 }
 
 static void mh_update_maildir (struct maildir *md, struct mh_sequences *mhs)
 {
   int i;
   short f;
   char *p;
-  
+
   for (; md; md = md->next)
   {
     if ((p = strrchr (md->h->path, '/')))
       p++;
     else
       p = md->h->path;
 
-    i = atoi (p);
+    if (mutt_atoi (p, &i) < 0)
+      continue;
     f = mhs_check (mhs, i);
-    
-    md->h->read    = (f & MH_SEQ_UNSEEN)  ? 0 : 1;
+
+    md->h->read = (f & MH_SEQ_UNSEEN) ? 0 : 1;
     md->h->flagged = (f & MH_SEQ_FLAGGED) ? 1 : 0;
     md->h->replied = (f & MH_SEQ_REPLIED) ? 1 : 0;
   }
 }
 
 /* maildir support */
 
-static void maildir_free_entry(struct maildir **md)
+static void maildir_free_entry (struct maildir **md)
 {
-  if(!md || !*md)
+  if (!md || !*md)
     return;
 
-  safe_free((void **) &(*md)->canon_fname);
-  if((*md)->h)
-    mutt_free_header(&(*md)->h);
+  FREE (&(*md)->canon_fname);
+  if ((*md)->h)
+    mutt_free_header (&(*md)->h);
 
-  safe_free((void **) md);
+  FREE (md);		/* __FREE_CHECKED__ */
 }
-  
-static void maildir_free_maildir(struct maildir **md)
+
+static void maildir_free_maildir (struct maildir **md)
 {
   struct maildir *p, *q;
-  
-  if(!md || !*md)
+
+  if (!md || !*md)
     return;
-  
-  for(p = *md; p; p = q)
+
+  for (p = *md; p; p = q)
   {
     q = p->next;
-    maildir_free_entry(&p);
+    maildir_free_entry (&p);
   }
 }
 
-static void maildir_parse_flags(HEADER *h, const char *path)
+static void maildir_parse_flags (HEADER * h, const char *path)
 {
-  char *p;
+  char *p, *q = NULL;
 
   h->flagged = 0;
   h->read = 0;
   h->replied = 0;
-  
+
   if ((p = strrchr (path, ':')) != NULL && mutt_strncmp (p + 1, "2,", 2) == 0)
   {
     p += 3;
+    
+    mutt_str_replace (&h->maildir_flags, p);
+    q = h->maildir_flags;
+
     while (*p)
     {
       switch (*p)
       {
-	case 'F':
-	
+      case 'F':
+
 	h->flagged = 1;
 	break;
-	
-	case 'S': /* seen */
-	
+
+      case 'S':		/* seen */
+
 	h->read = 1;
 	break;
-	
-	case 'R': /* replied */
-	
+
+      case 'R':		/* replied */
+
 	h->replied = 1;
 	break;
 
-	case 'T': /* trashed */
-	h->trash   = 1;
+      case 'T':		/* trashed */
+	h->trash = 1;
 	h->deleted = 1;
 	break;
+      
+      default:
+	*q++ = *p;
+	break;
       }
       p++;
     }
   }
+  
+  if (q == h->maildir_flags)
+    FREE (&h->maildir_flags);
+  else if (q)
+    *q = '\0';
 }
 
-static void maildir_update_mtime(CONTEXT *ctx)
+static void maildir_update_mtime (CONTEXT * ctx)
 {
   char buf[_POSIX_PATH_MAX];
   struct stat st;
-  
-  if(ctx->magic == M_MAILDIR)
+  struct mh_data *data = mh_data (ctx);
+
+  if (ctx->magic == M_MAILDIR)
   {
-    snprintf(buf, sizeof(buf), "%s/%s", ctx->path, "cur");
-    if(stat (buf, &st) == 0)
-      ctx->mtime_cur = st.st_mtime;
-    snprintf(buf, sizeof(buf), "%s/%s", ctx->path, "new");
+    snprintf (buf, sizeof (buf), "%s/%s", ctx->path, "cur");
+    if (stat (buf, &st) == 0)
+      data->mtime_cur = st.st_mtime;
+    snprintf (buf, sizeof (buf), "%s/%s", ctx->path, "new");
   }
   else
   {
     snprintf (buf, sizeof (buf), "%s/.mh_sequences", ctx->path);
     if (stat (buf, &st) == 0)
-      ctx->mtime_cur = st.st_mtime;
-    
-    strfcpy(buf, ctx->path, sizeof(buf));
+      data->mtime_cur = st.st_mtime;
+
+    strfcpy (buf, ctx->path, sizeof (buf));
   }
-  
-  if(stat(buf, &st) == 0)
+
+  if (stat (buf, &st) == 0)
     ctx->mtime = st.st_mtime;
 }
 
-static HEADER *maildir_parse_message(int magic, const char *fname, int is_old)
+/* 
+ * Actually parse a maildir message.  This may also be used to fill
+ * out a fake header structure generated by lazy maildir parsing.
+ */
+static HEADER *maildir_parse_message (int magic, const char *fname,
+				      int is_old, HEADER * _h)
 {
   FILE *f;
-  HEADER *h = NULL;
+  HEADER *h = _h;
   struct stat st;
-  
+
   if ((f = fopen (fname, "r")) != NULL)
   {
-    h = mutt_new_header();
+    if (!h)
+      h = mutt_new_header ();
     h->env = mutt_read_rfc822_header (f, h, 0, 0);
 
     fstat (fileno (f), &st);
-    fclose (f);
+    safe_fclose (&f);
 
     if (!h->received)
       h->received = h->date_sent;
 
-    if (h->content->length <= 0)
-      h->content->length = st.st_size - h->content->offset;
+    /* always update the length since we have fresh information available. */
+    h->content->length = st.st_size - h->content->offset;
 
     h->index = -1;
 
     if (magic == M_MAILDIR)
     {
-      /* maildir stores its flags in the filename, so ignore the flags in
-       * the header of the message
+      /* 
+       * maildir stores its flags in the filename, so ignore the
+       * flags in the header of the message 
        */
 
       h->old = is_old;
-      maildir_parse_flags(h, fname);
-    }
-  }
-  return h;
-}
-
-/* note that this routine will _not_ modify the context given by ctx. */
-
-static int maildir_parse_entry(CONTEXT *ctx, struct maildir ***last,
-				const char *subdir, const char *fname,
-				int *count, int is_old)
-{
-  struct maildir *entry;
-  HEADER *h;
-  char buf[_POSIX_PATH_MAX];
-
-  if(subdir)
-    snprintf(buf, sizeof(buf), "%s/%s/%s", ctx->path, subdir, fname);
-  else
-    snprintf(buf, sizeof(buf), "%s/%s", ctx->path, fname);
-  
-  if((h = maildir_parse_message(ctx->magic, buf, is_old)) != NULL)
-  {
-    if(count)
-    {
-      (*count)++;  
-      if (!ctx->quiet && ReadInc && ((*count % ReadInc) == 0 || *count == 1))
-	mutt_message (_("Reading %s... %d"), ctx->path, *count);
-    }
-
-    if (subdir)
-    {
-      snprintf (buf, sizeof (buf), "%s/%s", subdir, fname);
-      h->path = safe_strdup (buf);
+      maildir_parse_flags (h, fname);
     }
-    else
-      h->path = safe_strdup (fname);
-    
-    entry = safe_calloc(sizeof(struct maildir), 1);
-    entry->h = h;
-    **last = entry;
-    *last = &entry->next;
-    
-    return 0;
+    return h;
   }
-  
-  return -1;
+  return NULL;
 }
 
 /* Ignore the garbage files.  A valid MH message consists of only
  * digits.  Deleted message get moved to a filename with a comma before
  * it.
  */
