 	if (p->init)
 	{
 	  char *s = (char *) p->init;
 
 	  pp->rx = safe_calloc (1, sizeof (regex_t));
 	  pp->pattern = safe_strdup ((char *) p->init);
-	  if (mutt_strcmp (p->option, "alternates") == 0)
-	    flags |= REG_ICASE;
-	  else if (mutt_strcmp (p->option, "mask") != 0)
+	  if (mutt_strcmp (p->option, "mask") != 0)
 	    flags |= mutt_which_case ((const char *) p->init);
 	  if (mutt_strcmp (p->option, "mask") == 0 && *s == '!')
 	  {
 	    s++;
 	    pp->not = 1;
 	  }
 	  if (REGCOMP (pp->rx, s, flags) != 0)
 	  {
 	    fprintf (stderr, _("mutt_restore_default(%s): error in regexp: %s\n"),
 		     p->option, pp->pattern);
 	    FREE (&pp->pattern);
-	    regfree (pp->rx);
 	    FREE (&pp->rx);
 	  }
 	}
       }
       break;
   }
 
-  if (p->flags & R_INDEX)
-    set_option (OPTFORCEREDRAWINDEX);
-  if (p->flags & R_PAGER)
-    set_option (OPTFORCEREDRAWPAGER);
-  if (p->flags & R_RESORT_SUB)
-    set_option (OPTSORTSUBTHREADS);
-  if (p->flags & R_RESORT)
-    set_option (OPTNEEDRESORT);
-  if (p->flags & R_RESORT_INIT)
-    set_option (OPTRESORTINIT);
+  if (p->flags & R_INDEX)
+    set_option (OPTFORCEREDRAWINDEX);
+  if (p->flags & R_PAGER)
+    set_option (OPTFORCEREDRAWPAGER);
+  if (p->flags & R_RESORT_SUB)
+    set_option (OPTSORTSUBTHREADS);
+  if (p->flags & R_RESORT)
+    set_option (OPTNEEDRESORT);
+  if (p->flags & R_RESORT_INIT)
+    set_option (OPTRESORTINIT);
+  if (p->flags & R_TREE)
+    set_option (OPTREDRAWTREE);
+}
+
+static size_t escape_string (char *dst, size_t len, const char* src)
+{
+  char* p = dst;
+
+  if (!len)
+    return 0;
+  len--; /* save room for \0 */
+#define ESC_CHAR(C)	do { *p++ = '\\'; if (p - dst < len) *p++ = C; } while(0)
+  while (p - dst < len && src && *src)
+  {
+    switch (*src)
+    {
+    case '\n':
+      ESC_CHAR('n');
+      break;
+    case '\r':
+      ESC_CHAR('r');
+      break;
+    case '\t':
+      ESC_CHAR('t');
+      break;
+    default:
+      if ((*src == '\\' || *src == '"') && p - dst < len - 1)
+	*p++ = '\\';
+      *p++ = *src;
+    }
+    src++;
+  }
+#undef ESC_CHAR
+  *p = '\0';
+  return p - dst;
+}
+
+static void pretty_var (char *dst, size_t len, const char *option, const char *val)
+{
+  char *p;
+
+  if (!len)
+    return;
+
+  strfcpy (dst, option, len);
+  len--; /* save room for \0 */
+  p = dst + mutt_strlen (dst);
+
+  if (p - dst < len)
+    *p++ = '=';
+  if (p - dst < len)
+    *p++ = '"';
+  p += escape_string (p, len - (p - dst) + 1, val);	/* \0 terminate it */
+  if (p - dst < len)
+    *p++ = '"';
+  *p = 0;
+}
+
+static int check_charset (struct option_t *opt, const char *val)
+{
+  char *p, *q = NULL, *s = safe_strdup (val);
+  int rc = 0, strict = strcmp (opt->option, "send_charset") == 0;
+
+  if (!s)
+    return rc;
+
+  for (p = strtok_r (s, ":", &q); p; p = strtok_r (NULL, ":", &q))
+  {
+    if (!*p)
+      continue;
+    if (mutt_check_charset (p, strict) < 0)
+    {
+      rc = -1;
+      break;
+    }
+  }
+
+  FREE(&s);
+  return rc;
 }
 
 static int parse_set (BUFFER *tmp, BUFFER *s, unsigned long data, BUFFER *err)
 {
-  int idx, query, unset, inv, reset, r = 0;
-  char *p, scratch[_POSIX_PATH_MAX];
+  int query, unset, inv, reset, r = 0;
+  int idx = -1;
+  const char *p;
+  char scratch[_POSIX_PATH_MAX];
+  char* myvar;
 
   while (MoreArgs (s))
   {
     /* reset state variables */
     query = 0;
     unset = data & M_SET_UNSET;
     inv = data & M_SET_INV;
     reset = data & M_SET_RESET;
+    myvar = NULL;
 
     if (*s->dptr == '?')
     {
       query = 1;
       s->dptr++;
     }
