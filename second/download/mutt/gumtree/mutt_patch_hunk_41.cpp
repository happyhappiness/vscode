   }
   while (MoreArgs (s));
 
   return 0;
 }
 
+static void _alternates_clean (void)
+{
+  int i;
+  if (Context && Context->msgcount) 
+  {
+    for (i = 0; i < Context->msgcount; i++)
+      Context->hdrs[i]->recip_valid = 0;
+  }
+}
+
+static int parse_alternates (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
+{
+  group_context_t *gc = NULL;
+  
+  _alternates_clean();
+
+  do
+  {
+    mutt_extract_token (buf, s, 0);
+
+    if (parse_group_context (&gc, buf, s, data, err) == -1)
+      goto bail;
+
+    mutt_remove_from_rx_list (&UnAlternates, buf->data);
+
+    if (mutt_add_to_rx_list (&Alternates, buf->data, REG_ICASE, err) != 0)
+      goto bail;
+
+    if (mutt_group_context_add_rx (gc, buf->data, REG_ICASE, err) != 0)
+      goto bail;
+  }
+  while (MoreArgs (s));
+  
+  mutt_group_context_destroy (&gc);
+  return 0;
+  
+ bail:
+  mutt_group_context_destroy (&gc);
+  return -1;
+}
+
+static int parse_unalternates (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
+{
+  _alternates_clean();
+  do
+  {
+    mutt_extract_token (buf, s, 0);
+    mutt_remove_from_rx_list (&Alternates, buf->data);
+
+    if (mutt_strcmp (buf->data, "*") &&
+	mutt_add_to_rx_list (&UnAlternates, buf->data, REG_ICASE, err) != 0)
+      return -1;
+
+  }
+  while (MoreArgs (s));
+
+  return 0;
+}
+
+static int parse_spam_list (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
+{
+  BUFFER templ;
+
+  mutt_buffer_init (&templ);
+
+  /* Insist on at least one parameter */
+  if (!MoreArgs(s))
+  {
+    if (data == M_SPAM)
+      strfcpy(err->data, _("spam: no matching pattern"), err->dsize);
+    else
+      strfcpy(err->data, _("nospam: no matching pattern"), err->dsize);
+    return -1;
+  }
+
+  /* Extract the first token, a regexp */
+  mutt_extract_token (buf, s, 0);
+
+  /* data should be either M_SPAM or M_NOSPAM. M_SPAM is for spam commands. */
+  if (data == M_SPAM)
+  {
+    /* If there's a second parameter, it's a template for the spam tag. */
+    if (MoreArgs(s))
+    {
+      mutt_extract_token (&templ, s, 0);
+
+      /* Add to the spam list. */
+      if (add_to_spam_list (&SpamList, buf->data, templ.data, err) != 0) {
+	  FREE(&templ.data);
+          return -1;
+      }
+      FREE(&templ.data);
+    }
+
+    /* If not, try to remove from the nospam list. */
+    else
+    {
+      mutt_remove_from_rx_list(&NoSpamList, buf->data);
+    }
+
+    return 0;
+  }
+
+  /* M_NOSPAM is for nospam commands. */
+  else if (data == M_NOSPAM)
+  {
+    /* nospam only ever has one parameter. */
+
+    /* "*" is a special case. */
+    if (!mutt_strcmp(buf->data, "*"))
+    {
+      mutt_free_spam_list (&SpamList);
+      mutt_free_rx_list (&NoSpamList);
+      return 0;
+    }
+
+    /* If it's on the spam list, just remove it. */
+    if (remove_from_spam_list(&SpamList, buf->data) != 0)
+      return 0;
+
+    /* Otherwise, add it to the nospam list. */
+    if (mutt_add_to_rx_list (&NoSpamList, buf->data, REG_ICASE, err) != 0)
+      return -1;
+
+    return 0;
+  }
+
+  /* This should not happen. */
+  strfcpy(err->data, "This is no good at all.", err->dsize);
+  return -1;
+}
+
+
 static int parse_unlist (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
 {
   do
   {
     mutt_extract_token (buf, s, 0);
+    /*
+     * Check for deletion of entire list
+     */
+    if (mutt_strcmp (buf->data, "*") == 0)
+    {
+      mutt_free_list ((LIST **) data);
+      break;
+    }
     remove_from_list ((LIST **) data, buf->data);
   }
   while (MoreArgs (s));
 
   return 0;
 }
 
+static int parse_lists (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
+{
+  group_context_t *gc = NULL;
+
+  do
+  {
+    mutt_extract_token (buf, s, 0);
+    
+    if (parse_group_context (&gc, buf, s, data, err) == -1)
+      goto bail;
+    
+    mutt_remove_from_rx_list (&UnMailLists, buf->data);
+    
+    if (mutt_add_to_rx_list (&MailLists, buf->data, REG_ICASE, err) != 0)
+      goto bail;
+    
+    if (mutt_group_context_add_rx (gc, buf->data, REG_ICASE, err) != 0)
+      goto bail;
+  }
+  while (MoreArgs (s));
+
+  mutt_group_context_destroy (&gc);
+  return 0;
+  
+ bail:
+  mutt_group_context_destroy (&gc);
+  return -1;
+}
+
+typedef enum group_state_t {
+  NONE, RX, ADDR
+} group_state_t;
+
+static int parse_group (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
+{
+  group_context_t *gc = NULL;
+  group_state_t state = NONE;
+  ADDRESS *addr = NULL;
+  char *estr = NULL;
+
+  do
+  {
+    mutt_extract_token (buf, s, 0);
+    if (parse_group_context (&gc, buf, s, data, err) == -1)
+      goto bail;
+
+    if (data == M_UNGROUP && !mutt_strcasecmp (buf->data, "*"))
+    {
+      if (mutt_group_context_clear (&gc) < 0)
+	goto bail;
+      goto out;
+    }
+
+    if (!mutt_strcasecmp (buf->data, "-rx"))
+      state = RX;
+    else if (!mutt_strcasecmp (buf->data, "-addr"))
+      state = ADDR;
+    else
+    {
+      switch (state)
+      {
+	case NONE:
+	  snprintf (err->data, err->dsize, _("%sgroup: missing -rx or -addr."),
+		   data == M_UNGROUP ? "un" : "");
+	  goto bail;
+
+	case RX:
+	  if (data == M_GROUP &&
+	      mutt_group_context_add_rx (gc, buf->data, REG_ICASE, err) != 0)
+	    goto bail;
+	  else if (data == M_UNGROUP &&
+		   mutt_group_context_remove_rx (gc, buf->data) < 0)
+	    goto bail;
+	  break;
+
+	case ADDR:
+	  if ((addr = mutt_parse_adrlist (NULL, buf->data)) == NULL)
+	    goto bail;
+	  if (mutt_addrlist_to_idna (addr, &estr))
+	  { 
+	    snprintf (err->data, err->dsize, _("%sgroup: warning: bad IDN '%s'.\n"),
+		      data == 1 ? "un" : "", estr);
+	    goto bail;
+	  }
+	  if (data == M_GROUP)
+	    mutt_group_context_add_adrlist (gc, addr);
+	  else if (data == M_UNGROUP)
+	    mutt_group_context_remove_adrlist (gc, addr);
+	  rfc822_free_address (&addr);
+	  break;
+      }
+    }
+  } while (MoreArgs (s));
+
+out:
+  mutt_group_context_destroy (&gc);
+  return 0;
+
+bail:
+  mutt_group_context_destroy (&gc);
+  return -1;
+}
+
+/* always wise to do what someone else did before */
+static void _attachments_clean (void)
+{
+  int i;
+  if (Context && Context->msgcount) 
+  {
+    for (i = 0; i < Context->msgcount; i++)
+      Context->hdrs[i]->attach_valid = 0;
+  }
+}
+
+static int parse_attach_list (BUFFER *buf, BUFFER *s, LIST **ldata, BUFFER *err)
+{
+  ATTACH_MATCH *a;
+  LIST *listp, *lastp;
+  char *p;
+  char *tmpminor;
+  int len;
+  int ret;
+
+  /* Find the last item in the list that data points to. */
+  lastp = NULL;
+  dprint(5, (debugfile, "parse_attach_list: ldata = %p, *ldata = %p\n",
+	      (void *)ldata, (void *)*ldata));
+  for (listp = *ldata; listp; listp = listp->next)
+  {
+    a = (ATTACH_MATCH *)listp->data;
+    dprint(5, (debugfile, "parse_attach_list: skipping %s/%s\n",
+		a->major, a->minor));
+    lastp = listp;
+  }
+
+  do
+  {
+    mutt_extract_token (buf, s, 0);
+
+    if (!buf->data || *buf->data == '\0')
+      continue;
+   
+    a = safe_malloc(sizeof(ATTACH_MATCH));
+
+    /* some cheap hacks that I expect to remove */
+    if (!ascii_strcasecmp(buf->data, "any"))
+      a->major = safe_strdup("*/.*");
+    else if (!ascii_strcasecmp(buf->data, "none"))
+      a->major = safe_strdup("cheap_hack/this_should_never_match");
+    else
+      a->major = safe_strdup(buf->data);
+
+    if ((p = strchr(a->major, '/')))
+    {
+      *p = '\0';
+      ++p;
+      a->minor = p;
+    }
+    else
+    {
+      a->minor = "unknown";
+    }
+
+    len = strlen(a->minor);
+    tmpminor = safe_malloc(len+3);
+    strcpy(&tmpminor[1], a->minor); /* __STRCPY_CHECKED__ */
+    tmpminor[0] = '^';
+    tmpminor[len+1] = '$';
+    tmpminor[len+2] = '\0';
+
+    a->major_int = mutt_check_mime_type(a->major);
+    ret = REGCOMP(&a->minor_rx, tmpminor, REG_ICASE);
+
+    FREE(&tmpminor);
+
+    if (ret)
+    {
+      regerror(ret, &a->minor_rx, err->data, err->dsize);
+      FREE(&a->major);
+      FREE(&a);
+      return -1;
+    }
+
+    dprint(5, (debugfile, "parse_attach_list: added %s/%s [%d]\n",
+		a->major, a->minor, a->major_int));
+
+    listp = safe_malloc(sizeof(LIST));
+    listp->data = (char *)a;
+    listp->next = NULL;
+    if (lastp)
+    {
+      lastp->next = listp;
+    }
+    else
+    {
+      *ldata = listp;
+    }
+    lastp = listp;
+  }
+  while (MoreArgs (s));
+   
+  _attachments_clean();
+  return 0;
+}
+
+static int parse_unattach_list (BUFFER *buf, BUFFER *s, LIST **ldata, BUFFER *err)
+{
+  ATTACH_MATCH *a;
+  LIST *lp, *lastp, *newlp;
+  char *tmp;
+  int major;
+  char *minor;
+
+  do
+  {
+    mutt_extract_token (buf, s, 0);
+
+    if (!ascii_strcasecmp(buf->data, "any"))
+      tmp = safe_strdup("*/.*");
+    else if (!ascii_strcasecmp(buf->data, "none"))
+      tmp = safe_strdup("cheap_hack/this_should_never_match");
+    else
+      tmp = safe_strdup(buf->data);
+
+    if ((minor = strchr(tmp, '/')))
+    {
+      *minor = '\0';
+      ++minor;
+    }
+    else
+    {
+      minor = "unknown";
+    }
+    major = mutt_check_mime_type(tmp);
+
+    /* We must do our own walk here because remove_from_list() will only
+     * remove the LIST->data, not anything pointed to by the LIST->data. */
+    lastp = NULL;
+    for(lp = *ldata; lp; )
+    {
+      a = (ATTACH_MATCH *)lp->data;
+      dprint(5, (debugfile, "parse_unattach_list: check %s/%s [%d] : %s/%s [%d]\n",
+		  a->major, a->minor, a->major_int, tmp, minor, major));
+      if (a->major_int == major && !mutt_strcasecmp(minor, a->minor))
+      {
+	dprint(5, (debugfile, "parse_unattach_list: removed %s/%s [%d]\n",
+		    a->major, a->minor, a->major_int));
+	regfree(&a->minor_rx);
+	FREE(&a->major);
+
+	/* Relink backward */
+	if (lastp)
+	  lastp->next = lp->next;
+	else
+	  *ldata = lp->next;
+
+        newlp = lp->next;
+        FREE(&lp->data);	/* same as a */
+        FREE(&lp);
+        lp = newlp;
+        continue;
+      }
+
+      lastp = lp;
+      lp = lp->next;
+    }
+
+  }
+  while (MoreArgs (s));
+   
+  FREE(&tmp);
+  _attachments_clean();
+  return 0;
+}
+
+static int print_attach_list (LIST *lp, char op, char *name)
+{
+  while (lp) {
+    printf("attachments %c%s %s/%s\n", op, name,
+           ((ATTACH_MATCH *)lp->data)->major,
+           ((ATTACH_MATCH *)lp->data)->minor);
+    lp = lp->next;
+  }
+
+  return 0;
+}
+
+
+static int parse_attachments (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
+{
+  char op, *category;
+  LIST **listp;
+
+  mutt_extract_token(buf, s, 0);
+  if (!buf->data || *buf->data == '\0') {
+    strfcpy(err->data, _("attachments: no disposition"), err->dsize);
+    return -1;
+  }
+
+  category = buf->data;
+  op = *category++;
+
+  if (op == '?') {
+    mutt_endwin (NULL);
+    fflush (stdout);
+    printf("\nCurrent attachments settings:\n\n");
+    print_attach_list(AttachAllow,   '+', "A");
+    print_attach_list(AttachExclude, '-', "A");
+    print_attach_list(InlineAllow,   '+', "I");
+    print_attach_list(InlineExclude, '-', "I");
+    set_option (OPTFORCEREDRAWINDEX);
+    set_option (OPTFORCEREDRAWPAGER);
+    mutt_any_key_to_continue (NULL);
+    return 0;
+  }
+
+  if (op != '+' && op != '-') {
+    op = '+';
+    category--;
+  }
+  if (!ascii_strncasecmp(category, "attachment", strlen(category))) {
+    if (op == '+')
+      listp = &AttachAllow;
+    else
+      listp = &AttachExclude;
+  }
+  else if (!ascii_strncasecmp(category, "inline", strlen(category))) {
+    if (op == '+')
+      listp = &InlineAllow;
+    else
+      listp = &InlineExclude;
+  }
+  else {
+    strfcpy(err->data, _("attachments: invalid disposition"), err->dsize);
+    return -1;
+  }
+
+  return parse_attach_list(buf, s, listp, err);
+}
+
+static int parse_unattachments (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
+{
+  char op, *p;
+  LIST **listp;
+
+  mutt_extract_token(buf, s, 0);
+  if (!buf->data || *buf->data == '\0') {
+    strfcpy(err->data, _("unattachments: no disposition"), err->dsize);
+    return -1;
+  }
+
+  p = buf->data;
+  op = *p++;
+  if (op != '+' && op != '-') {
+    op = '+';
+    p--;
+  }
+  if (!ascii_strncasecmp(p, "attachment", strlen(p))) {
+    if (op == '+')
+      listp = &AttachAllow;
+    else
+      listp = &AttachExclude;
+  }
+  else if (!ascii_strncasecmp(p, "inline", strlen(p))) {
+    if (op == '+')
+      listp = &InlineAllow;
+    else
+      listp = &InlineExclude;
+  }
+  else {
+    strfcpy(err->data, _("unattachments: invalid disposition"), err->dsize);
+    return -1;
+  }
+
+  return parse_unattach_list(buf, s, listp, err);
+}
 
 static int parse_unlists (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
 {
   do
   {
     mutt_extract_token (buf, s, 0);
-    remove_from_list (&MailLists, buf->data);
-    remove_from_list (&SubscribedLists, buf->data);
+    mutt_remove_from_rx_list (&SubscribedLists, buf->data);
+    mutt_remove_from_rx_list (&MailLists, buf->data);
+    
+    if (mutt_strcmp (buf->data, "*") && 
+	mutt_add_to_rx_list (&UnMailLists, buf->data, REG_ICASE, err) != 0)
+      return -1;
   }
   while (MoreArgs (s));
 
   return 0;
 }
 
 static int parse_subscribe (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
 {
+  group_context_t *gc = NULL;
+  
   do
   {
     mutt_extract_token (buf, s, 0);
-    add_to_list (&MailLists, buf->data);
-    add_to_list (&SubscribedLists, buf->data);
+
+    if (parse_group_context (&gc, buf, s, data, err) == -1)
+      goto bail;
+    
+    mutt_remove_from_rx_list (&UnMailLists, buf->data);
+    mutt_remove_from_rx_list (&UnSubscribedLists, buf->data);
+
+    if (mutt_add_to_rx_list (&MailLists, buf->data, REG_ICASE, err) != 0)
+      goto bail;
+    if (mutt_add_to_rx_list (&SubscribedLists, buf->data, REG_ICASE, err) != 0)
+      goto bail;
+    if (mutt_group_context_add_rx (gc, buf->data, REG_ICASE, err) != 0)
+      goto bail;
+  }
+  while (MoreArgs (s));
+  
+  mutt_group_context_destroy (&gc);
+  return 0;
+  
+ bail:
+  mutt_group_context_destroy (&gc);
+  return -1;
+}
+
+static int parse_unsubscribe (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
+{
+  do
+  {
+    mutt_extract_token (buf, s, 0);
+    mutt_remove_from_rx_list (&SubscribedLists, buf->data);
+    
+    if (mutt_strcmp (buf->data, "*") &&
+	mutt_add_to_rx_list (&UnSubscribedLists, buf->data, REG_ICASE, err) != 0)
+      return -1;
   }
   while (MoreArgs (s));
 
   return 0;
 }
   
