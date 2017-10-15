       fprintf (f, "?");
     }
   }
   return (maxwidth - n);
 }
 
+static int get_wrapped_width (const char *t, size_t wid)
+{
+  wchar_t wc;
+  size_t k;
+  size_t m, n;
+  size_t len = mutt_strlen (t);
+  const char *s = t;
+  mbstate_t mbstate;
+
+  memset (&mbstate, 0, sizeof (mbstate));
+  for (m = wid, n = 0;
+       len && (k = mbrtowc (&wc, s, len, &mbstate)) && (n <= wid);
+       s += k, len -= k)
+  {
+    if (*s == ' ')
+      m = n;
+    if (k == (size_t)(-1) || k == (size_t)(-2))
+    {
+      k = (k == (size_t)(-1)) ? 1 : len;
+      wc = replacement_char ();
+    }
+    if (!IsWPrint (wc))
+      wc = '?';
+    n += wcwidth (wc);
+  }
+  if (n > wid)
+    n = m;
+  else
+    n = wid;
+  return n;
+}
+
 static int pad (FILE *f, int col, int i)
 {
   char fmt[8];
 
   if (col < i)
   {
