   if (*pt == '=') /* abort if no var before the '=' */
     return 0;
 
   if (mutt_strncmp (buffer, "set", 3) == 0)
   {
     int idx;
+    char val[LONG_STRING];
+    const char *myvarval;
+
     strfcpy (var, pt, sizeof (var));
     /* ignore the trailing '=' when comparing */
     var[mutt_strlen (var) - 1] = 0;
-    if ((idx = mutt_option_index (var)) == -1) 
+    if ((idx = mutt_option_index (var)) == -1)
+    {
+      if ((myvarval = myvar_get(var)) != NULL)
+      {
+	pretty_var (pt, len - (pt - buffer), var, myvarval);
+	return 1;
+      }
       return 0; /* no such variable. */
-    else
+    }
+    else if (var_to_string (idx, val, sizeof (val)))
     {
-      char tmp [LONG_STRING], tmp2[LONG_STRING];
-      char *s, *d;
-      size_t dlen = buffer + len - pt - spaces;
-      char *vals[] = { "no", "yes", "ask-no", "ask-yes" };
+      snprintf (pt, len - (pt - buffer), "%s=\"%s\"", var, val);
+      return 1;
+    }
+  }
+  return 0;
+}
 
-      tmp[0] = '\0';
+static int var_to_string (int idx, char* val, size_t len)
+{
+  char tmp[LONG_STRING];
+  static const char * const vals[] = { "no", "yes", "ask-no", "ask-yes" };
 
-      if ((DTYPE(MuttVars[idx].type) == DT_STR) || 
-	  (DTYPE(MuttVars[idx].type) == DT_PATH) ||
-	  (DTYPE(MuttVars[idx].type) == DT_RX))
-      {
-	strfcpy (tmp, NONULL (*((char **) MuttVars[idx].data)), sizeof (tmp));
-	if (DTYPE (MuttVars[idx].type) == DT_PATH)
-	  mutt_pretty_mailbox (tmp);
-      }
-      else if (DTYPE (MuttVars[idx].type) == DT_ADDR)
-      {
-	rfc822_write_address (tmp, sizeof (tmp), *((ADDRESS **) MuttVars[idx].data));
-      }
-      else if (DTYPE (MuttVars[idx].type) == DT_QUAD)
-	strfcpy (tmp, vals[quadoption (MuttVars[idx].data)], sizeof (tmp));
-      else if (DTYPE (MuttVars[idx].type) == DT_NUM)
-	snprintf (tmp, sizeof (tmp), "%d", (*((short *) MuttVars[idx].data)));
-      else if (DTYPE (MuttVars[idx].type) == DT_SORT)
-      {
-	const struct mapping_t *map;
-	char *p;
+  tmp[0] = '\0';
+
+  if ((DTYPE(MuttVars[idx].type) == DT_STR) ||
+      (DTYPE(MuttVars[idx].type) == DT_PATH) ||
+      (DTYPE(MuttVars[idx].type) == DT_RX))
+  {
+    strfcpy (tmp, NONULL (*((char **) MuttVars[idx].data)), sizeof (tmp));
+    if (DTYPE (MuttVars[idx].type) == DT_PATH)
+      mutt_pretty_mailbox (tmp, sizeof (tmp));
+  }
+  else if (DTYPE (MuttVars[idx].type) == DT_ADDR)
+  {
+    rfc822_write_address (tmp, sizeof (tmp), *((ADDRESS **) MuttVars[idx].data), 0);
+  }
+  else if (DTYPE (MuttVars[idx].type) == DT_QUAD)
+    strfcpy (tmp, vals[quadoption (MuttVars[idx].data)], sizeof (tmp));
+  else if (DTYPE (MuttVars[idx].type) == DT_NUM)
+  {
+    short sval = *((short *) MuttVars[idx].data);
+
+    /* avert your eyes, gentle reader */
+    if (mutt_strcmp (MuttVars[idx].option, "wrapmargin") == 0)
+      sval = sval > 0 ? 0 : -sval;
+
+    snprintf (tmp, sizeof (tmp), "%d", sval);
+  }
+  else if (DTYPE (MuttVars[idx].type) == DT_SORT)
+  {
+    const struct mapping_t *map;
+    const char *p;
+
+    switch (MuttVars[idx].type & DT_SUBTYPE_MASK)
+    {
+      case DT_SORT_ALIAS:
+        map = SortAliasMethods;
+        break;
+      case DT_SORT_BROWSER:
+        map = SortBrowserMethods;
+        break;
+      case DT_SORT_KEYS:
+        if ((WithCrypto & APPLICATION_PGP))
+          map = SortKeyMethods;
+        else
+          map = SortMethods;
+        break;
+      default:
+        map = SortMethods;
+        break;
+    }
+    p = mutt_getnamebyvalue (*((short *) MuttVars[idx].data) & SORT_MASK, map);
+    snprintf (tmp, sizeof (tmp), "%s%s%s",
+              (*((short *) MuttVars[idx].data) & SORT_REVERSE) ? "reverse-" : "",
+              (*((short *) MuttVars[idx].data) & SORT_LAST) ? "last-" : "",
+              p);
+  }
+  else if (DTYPE (MuttVars[idx].type) == DT_MAGIC)
+  {
+    char *p;
+
+    switch (DefaultMagic)
+    {
+      case M_MBOX:
+        p = "mbox";
+        break;
+      case M_MMDF:
+        p = "MMDF";
+        break;
+      case M_MH:
+        p = "MH";
+        break;
+      case M_MAILDIR:
+        p = "Maildir";
+        break;
+      default:
+        p = "unknown";
+    }
+    strfcpy (tmp, p, sizeof (tmp));
+  }
+  else if (DTYPE (MuttVars[idx].type) == DT_BOOL)
+    strfcpy (tmp, option (MuttVars[idx].data) ? "yes" : "no", sizeof (tmp));
+  else
+    return 0;
+
+  escape_string (val, len - 1, tmp);
+
+  return 1;
+}
+
+/* Implement the -Q command line flag */
+int mutt_query_variables (LIST *queries)
+{
+  LIST *p;
+  
+  char command[STRING];
+  
+  BUFFER err, token;
+
+  mutt_buffer_init (&err);
+  mutt_buffer_init (&token);
+
+  err.dsize = STRING;
+  err.data = safe_malloc (err.dsize);
+  
+  for (p = queries; p; p = p->next)
+  {
+    snprintf (command, sizeof (command), "set ?%s\n", p->data);
+    if (mutt_parse_rc_line (command, &token, &err) == -1)
+    {
+      fprintf (stderr, "%s\n", err.data);
+      FREE (&token.data);
+      FREE (&err.data);
+
+      return 1;
+    }
+    printf ("%s\n", err.data);
+  }
+  
+  FREE (&token.data);
+  FREE (&err.data);
+
+  return 0;
+}
+
+/* dump out the value of all the variables we have */
+int mutt_dump_variables (void)
+{
+  int i;
+  
+  char command[STRING];
+  
+  BUFFER err, token;
+
+  mutt_buffer_init (&err);
+  mutt_buffer_init (&token);
+
+  err.dsize = STRING;
+  err.data = safe_malloc (err.dsize);
+  
+  for (i = 0; MuttVars[i].option; i++)
+  {
+    if (MuttVars[i].type == DT_SYN)
+      continue;
+
+    snprintf (command, sizeof (command), "set ?%s\n", MuttVars[i].option);
+    if (mutt_parse_rc_line (command, &token, &err) == -1)
+    {
+      fprintf (stderr, "%s\n", err.data);
+      FREE (&token.data);
+      FREE (&err.data);
 
-	switch (MuttVars[idx].type & DT_SUBTYPE_MASK)
-	{
-	  case DT_SORT_ALIAS:
-	    map = SortAliasMethods;
-	    break;
-	  case DT_SORT_BROWSER:
-	    map = SortBrowserMethods;
-	    break;
-#ifdef HAVE_PGP
-	  case DT_SORT_KEYS:
-	    map = SortKeyMethods;
-	    break;
-#endif
-	  default:
-	    map = SortMethods;
-	    break;
-	}
-	p = mutt_getnamebyvalue (*((short *) MuttVars[idx].data) & SORT_MASK, map);
-	snprintf (tmp, sizeof (tmp), "%s%s%s",
-		  (*((short *) MuttVars[idx].data) & SORT_REVERSE) ? "reverse-" : "",
-		  (*((short *) MuttVars[idx].data) & SORT_LAST) ? "last-" : "",
-		  p);
-      }
-      else if (DTYPE (MuttVars[idx].type) == DT_BOOL)
-	strfcpy (tmp, option (MuttVars[idx].data) ? "yes" : "no", sizeof (tmp));
-      else
-	return 0;
-      
-      for (s = tmp, d = tmp2; *s && (d - tmp2) < sizeof (tmp2) - 2;)
-      {
-	if (*s == '\\' || *s == '"')
-	  *d++ = '\\';
-	*d++ = *s++;
-      }
-      *d = '\0';
-      
-      strfcpy (tmp, pt, sizeof (tmp));
-      snprintf (pt, dlen, "%s\"%s\"", tmp, tmp2);
-	  
       return 1;
     }
+    printf("%s\n", err.data);
   }
+  
+  FREE (&token.data);
+  FREE (&err.data);
+
   return 0;
 }
 
-char *mutt_getnamebyvalue (int val, const struct mapping_t *map)
+const char *mutt_getnamebyvalue (int val, const struct mapping_t *map)
 {
   int i;
 
   for (i=0; map[i].name; i++)
     if (map[i].value == val)
       return (map[i].name);
