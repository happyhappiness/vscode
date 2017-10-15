 {
   char *p;
   
   for (p = s + mutt_strlen (s) - 1 ; p >= s && ISSPACE (*p) ; p--)
     *p = 0;
 }
+
+/*
+ * Write the concatened pathname (dir + "/" + fname) into dst.
+ * The slash is ommitted when dir or fname is of 0 length.
+ * Returns NULL on error or a pointer to dst otherwise.
+ */
+char *mutt_concatn_path (char *dst, size_t dstlen,
+    const char *dir, size_t dirlen, const char *fname, size_t fnamelen)
+{
+  size_t req;
+  size_t offset = 0;
+
+  if (dstlen == 0)
+    return NULL; /* probably should not mask errors like this */
+
+  /* size check */
+  req = dirlen + fnamelen + 1; /* +1 for the trailing nul */
+  if (dirlen && fnamelen)
+    req++; /* when both components are non-nul, we add a "/" in between */
+  if (req > dstlen) { /* check for condition where the dst length is too short */
+    /* Two options here:
+     * 1) assert(0) or return NULL to signal error
+     * 2) copy as much of the path as will fit
+     * It doesn't appear that the return value is actually checked anywhere mutt_concat_path()
+     * is called, so we should just copy set dst to nul and let the calling function fail later.
+     */
+    dst[0] = 0; /* safe since we bail out early if dstlen == 0 */
+    return NULL;
+  }
+
+  if (dirlen) { /* when dir is not empty */
+    memcpy(dst, dir, dirlen);
+    offset = dirlen;
+    if (fnamelen)
+      dst[offset++] = '/';
+  }
+  if (fnamelen) { /* when fname is not empty */
+    memcpy(dst + offset, fname, fnamelen);
+    offset += fnamelen;
+  }
+  dst[offset] = 0;
+  return dst;
+}
+
+char *mutt_concat_path (char *d, const char *dir, const char *fname, size_t l)
+{
+  const char *fmt = "%s/%s";
+  
+  if (!*fname || (*dir && dir[strlen(dir)-1] == '/'))
+    fmt = "%s%s";
+  
+  snprintf (d, l, fmt, dir, fname);
+  return d;
+}
+
+const char *mutt_basename (const char *f)
+{
+  const char *p = strrchr (f, '/');
+  if (p)
+    return p + 1;
+  else
+    return f;
+}
+
+const char *
+mutt_strsysexit(int e)
+{
+  int i;
+  
+  for(i = 0; sysexits_h[i].str; i++)
+  {
+    if(e == sysexits_h[i].v)
+      break;
+  }
+  
+  return sysexits_h[i].str;
+}
+
+void mutt_debug (FILE *fp, const char *fmt, ...)
+{
+  va_list ap;
+  time_t now = time (NULL);
+  static char buf[23] = "";
+  static time_t last = 0;
+
+  if (now > last)
+  {
+    strftime (buf, sizeof (buf), "%Y-%m-%d %H:%M:%S", localtime (&now));
+    last = now;
+  }
+  fprintf (fp, "[%s] ", buf);
+  va_start (ap, fmt);
+  vfprintf (fp, fmt, ap);
+  va_end (ap);
+}
+
+int mutt_atos (const char *str, short *dst)
+{
+  int rc;
+  long res;
+  short tmp;
+  short *t = dst ? dst : &tmp;
+
+  *t = 0;
+
+  if ((rc = mutt_atol (str, &res)) < 0)
+    return rc;
+  if ((short) res != res)
+    return -2;
+
+  *t = (short) res;
+  return 0;
+}
+
+int mutt_atoi (const char *str, int *dst)
+{
+  int rc;
+  long res;
+  int tmp;
+  int *t = dst ? dst : &tmp;
+
+  *t = 0;
+
+  if ((rc = mutt_atol (str, &res)) < 0)
+    return rc;
+  if ((int) res != res)
+    return -2;
+
+  *t = (int) res;
+  return 0;
+}
+
+int mutt_atol (const char *str, long *dst)
+{
+  long r;
+  long *res = dst ? dst : &r;
+  char *e = NULL;
+
+  /* no input: 0 */
+  if (!str || !*str)
+  {
+    *res = 0;
+    return 0;
+  }
+
+  *res = strtol (str, &e, 10);
+  if ((*res == LONG_MAX && errno == ERANGE) ||
+      (e && *e != '\0'))
+    return -1;
+  return 0;
+}
