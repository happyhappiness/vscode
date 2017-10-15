     Aliases = new;
 
   strfcpy (buf, NONULL (AliasFile), sizeof (buf));
   if (mutt_get_field (_("Save to file: "), buf, sizeof (buf), M_FILE) != 0)
     return;
   mutt_expand_path (buf, sizeof (buf));
-  if ((rc = fopen (buf, "a")))
+  if ((rc = fopen (buf, "a+")))
   {
+    /* terminate existing file with \n if necessary */
+    if (fseek (rc, 0, SEEK_END))
+      goto fseek_err;
+    if (ftell(rc) > 0)
+    {
+      if (fseek (rc, -1, SEEK_CUR) < 0)
+	goto fseek_err;
+      if (fread(buf, 1, 1, rc) != 1)
+      {
+	mutt_perror (_("Error reading alias file"));
+	safe_fclose (&rc);
+	return;
+      }
+      if (fseek (rc, 0, SEEK_END) < 0)
+	goto fseek_err;
+      if (buf[0] != '\n')
+	fputc ('\n', rc);
+    }
+
+    if (mutt_check_alias_name (new->name, NULL, 0))
+      mutt_quote_filename (buf, sizeof (buf), new->name);
+    else
+      strfcpy (buf, new->name, sizeof (buf));
+    recode_buf (buf, sizeof (buf));
+    fprintf (rc, "alias %s ", buf);
     buf[0] = 0;
-    rfc822_write_address (buf, sizeof (buf), new->addr);
-    fprintf (rc, "alias %s ", new->name);
+    rfc822_write_address (buf, sizeof (buf), new->addr, 0);
+    recode_buf (buf, sizeof (buf));
     write_safe_address (rc, buf);
     fputc ('\n', rc);
-    fclose (rc);
+    safe_fclose (&rc);
     mutt_message _("Alias added.");
   }
   else
     mutt_perror (buf);
+
+  return;
+  
+  fseek_err:
+  mutt_perror (_("Error seeking in alias file"));
+  safe_fclose (&rc);
+  return;
+}
+
+/* 
+ * Sanity-check an alias name:  Only characters which are non-special to both
+ * the RFC 822 and the mutt configuration parser are permitted.
+ */
+
+int mutt_check_alias_name (const char *s, char *dest, size_t destlen)
+{
+  wchar_t wc;
+  mbstate_t mb;
+  size_t l;
+  int rv = 0, bad = 0, dry = !dest || !destlen;
+
+  memset (&mb, 0, sizeof (mbstate_t));
+
+  if (!dry)
+    destlen--;
+  for (; s && *s && (dry || destlen) &&
+       (l = mbrtowc (&wc, s, MB_CUR_MAX, &mb)) != 0;
+       s += l, destlen -= l)
+  {
+    bad = l == (size_t)(-1) || l == (size_t)(-2); /* conversion error */
+    bad = bad || (!dry && l > destlen);		/* too few room for mb char */
+    if (l == 1)
+      bad = bad || (strchr ("-_+=.", *s) == NULL && !iswalnum (wc));
+    else
+      bad = bad || !iswalnum (wc);
+    if (bad)
+    {
+      if (dry)
+	return -1;
+      *dest++ = '_';
+      rv = -1;
+    }
+    else if (!dry)
+    {
+      memcpy (dest, s, l);
+      dest += l;
+    }
+  }
+  if (!dry)
+    *dest = 0;
+  return rv;
 }
 
 /*
  * This routine looks to see if the user has an alias defined for the given
  * address.
  */
 ADDRESS *alias_reverse_lookup (ADDRESS *a)
 {
-  ALIAS *t = Aliases;
-  ADDRESS *ap;
-
   if (!a || !a->mailbox)
-    return NULL;
+      return NULL;
+  
+  return hash_find (ReverseAlias, a->mailbox);
+}
 
-  for (; t; t = t->next)
+void mutt_alias_add_reverse (ALIAS *t)
+{
+  ADDRESS *ap;
+  if (!t)
+    return;
+  
+  for (ap = t->addr; ap; ap = ap->next)
   {
-    /* cycle through all addresses if this is a group alias */
-    for (ap = t->addr; ap; ap = ap->next)
-    {
-      if (!ap->group && ap->mailbox &&
-	  ascii_strcasecmp (ap->mailbox, a->mailbox) == 0)
-	return ap;
-    }
+    if (!ap->group && ap->mailbox)
+      hash_insert (ReverseAlias, ap->mailbox, ap, 1);
+  }
+}
+
+void mutt_alias_delete_reverse (ALIAS *t)
+{
+  ADDRESS *ap;
+  if (!t)
+    return;
+  
+  for (ap = t->addr; ap; ap = ap->next)
+  {
+    if (!ap->group && ap->mailbox)
+      hash_delete (ReverseAlias, ap->mailbox, ap, NULL);
   }
-  return 0;
 }
 
 /* alias_complete() -- alias completion routine
  *
  * given a partial alias, this routine attempts to fill in the alias
  * from the alias list as much as possible. if given empty search string
