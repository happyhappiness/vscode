     state_attach_puts (_("\n[-- End of signed data --]\n"), s);
   
   return rc;
 }
 
 
+/* Obtain pointers to fingerprint or short or long key ID, if any.
+ * See mutt_crypt.h for details.
+ */
+const char* crypt_get_fingerprint_or_id (char *p, const char **pphint,
+    const char **ppl, const char **pps)
+{
+  const char *ps, *pl, *phint;
+  char *pfcopy, *pf, *s1, *s2;
+  char c;
+  int isid;
+  size_t hexdigits;
+
+  /* User input may be partial name, fingerprint or short or long key ID,
+   * independent of OPTPGPLONGIDS.
+   * Fingerprint without spaces is 40 hex digits (SHA-1) or 32 hex digits (MD5).
+   * Strip leading "0x" for key ID detection and prepare pl and ps to indicate
+   * if an ID was found and to simplify logic in the key loop's inner
+   * condition of the caller. */
+
+  pf = mutt_skip_whitespace (p);
+  if (!mutt_strncasecmp (pf, "0x", 2))
+    pf += 2;
+
+  /* Check if a fingerprint is given, must be hex digits only, blanks
+   * separating groups of 4 hex digits are allowed. Also pre-check for ID. */
+  isid = 2;             /* unknown */
+  hexdigits = 0;
+  s1 = pf;
+  do
+  {
+    c = *(s1++);
+    if (('0' <= c && c <= '9') || ('A' <= c && c <= 'F') || ('a' <= c && c <= 'f'))
+    {
+      ++hexdigits;
+      if (isid == 2)
+        isid = 1;       /* it is an ID so far */
+    }
+    else if (c)
+    {
+      isid = 0;         /* not an ID */
+      if (c == ' ' && ((hexdigits % 4) == 0))
+        ;               /* skip blank before or after 4 hex digits */
+      else
+        break;          /* any other character or position */
+    }
+  } while (c);
+
+  /* If at end of input, check for correct fingerprint length and copy if. */
+  pfcopy = (!c && ((hexdigits == 40) || (hexdigits == 32)) ? safe_strdup (pf) : NULL);
+
+  if (pfcopy)
+  {
+    /* Use pfcopy to strip all spaces from fingerprint and as hint. */
+    s1 = s2 = pfcopy;
+    do
+    {
+      *(s1++) = *(s2 = mutt_skip_whitespace (s2));
+    } while (*(s2++));
+
+    phint = pfcopy;
+    ps = pl = NULL;
+  }
+  else
+  {
+    phint = p;
+    ps = pl = NULL;
+    if (isid == 1)
+    {
+      if (mutt_strlen (pf) == 16)
+        pl = pf;        /* long key ID */
+      else if (mutt_strlen (pf) == 8)
+        ps = pf;        /* short key ID */
+    }
+  }
+
+  *pphint = phint;
+  *ppl = pl;
+  *pps = ps;
+  return pfcopy;
+}
+
+
+/*
+ * Used by pgp_findKeys and find_keys to check if a crypt-hook
+ * value is a key id.
+ */
+
+short crypt_is_numerical_keyid (const char *s)
+{
+  /* or should we require the "0x"? */
+  if (strncmp (s, "0x", 2) == 0)
+    s += 2;
+  if (strlen (s) % 8)
+    return 0;
+  while (*s)
+    if (strchr ("0123456789ABCDEFabcdef", *s++) == NULL)
+      return 0;
+
+  return 1;
+}
+
+
