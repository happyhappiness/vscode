 static void
 dump_kb_int64_t(StoreEntry * entry, const char *name, int64_t var)
 {
     storeAppendPrintf(entry, "%s %" PRId64 " %s\n", name, var, B_KBYTES_STR);
 }
 
+#if UNUSED_CODE
 static void
 parse_size_t(size_t * var)
 {
     int i;
     i = GetInteger();
     *var = (size_t) i;
 }
+#endif
 
 static void
 parse_b_size_t(size_t * var)
 {
     parseBytesLine(var, B_BYTES_STR);
 }
 
+#if !USE_DNSHELPER
+static void
+parse_b_ssize_t(ssize_t * var)
+{
+    parseBytesLineSigned(var, B_BYTES_STR);
+}
+#endif
+
 #if UNUSED_CODE
 static void
 parse_kb_size_t(size_t * var)
 {
     parseBytesLine(var, B_KBYTES_STR);
 }
