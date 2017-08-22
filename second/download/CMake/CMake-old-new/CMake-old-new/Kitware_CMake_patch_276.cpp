@@ -304,8 +304,15 @@ struct rar
     ssize_t		 avail_in;
     const unsigned char *next_in;
   } br;
+
+  /*
+   * Custom field to denote that this archive contains encrypted entries
+   */
+  int has_encrypted_entries;
 };
 
+static int archive_read_support_format_rar_capabilities(struct archive_read *);
+static int archive_read_format_rar_has_encrypted_entries(struct archive_read *);
 static int archive_read_format_rar_bid(struct archive_read *, int);
 static int archive_read_format_rar_options(struct archive_read *,
     const char *, const char *);
@@ -646,6 +653,12 @@ archive_read_support_format_rar(struct archive *_a)
   }
   memset(rar, 0, sizeof(*rar));
 
+	/*
+	 * Until enough data has been read, we cannot tell about
+	 * any encrypted entries yet.
+	 */
+	rar->has_encrypted_entries = ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW;
+
   r = __archive_read_register_format(a,
                                      rar,
                                      "rar",
@@ -655,14 +668,37 @@ archive_read_support_format_rar(struct archive *_a)
                                      archive_read_format_rar_read_data,
                                      archive_read_format_rar_read_data_skip,
                                      archive_read_format_rar_seek_data,
-                                     archive_read_format_rar_cleanup);
+                                     archive_read_format_rar_cleanup,
+                                     archive_read_support_format_rar_capabilities,
+                                     archive_read_format_rar_has_encrypted_entries);
 
   if (r != ARCHIVE_OK)
     free(rar);
   return (r);
 }
 
 static int
+archive_read_support_format_rar_capabilities(struct archive_read * a)
+{
+	(void)a; /* UNUSED */
+	return (ARCHIVE_READ_FORMAT_CAPS_ENCRYPT_DATA
+			| ARCHIVE_READ_FORMAT_CAPS_ENCRYPT_METADATA);
+}
+
+static int
+archive_read_format_rar_has_encrypted_entries(struct archive_read *_a)
+{
+	if (_a && _a->format) {
+		struct rar * rar = (struct rar *)_a->format->data;
+		if (rar) {
+			return rar->has_encrypted_entries;
+		}
+	}
+	return ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW;
+}
+
+
+static int
 archive_read_format_rar_bid(struct archive_read *a, int best_bid)
 {
   const char *p;
@@ -755,7 +791,7 @@ archive_read_format_rar_options(struct archive_read *a,
 {
   struct rar *rar;
   int ret = ARCHIVE_FAILED;
-        
+
   rar = (struct rar *)(a->format->data);
   if (strcmp(key, "hdrcharset")  == 0) {
     if (val == NULL || val[0] == 0)
@@ -797,6 +833,17 @@ archive_read_format_rar_read_header(struct archive_read *a,
 
   rar = (struct rar *)(a->format->data);
 
+  /*
+   * It should be sufficient to call archive_read_next_header() for
+   * a reader to determine if an entry is encrypted or not. If the
+   * encryption of an entry is only detectable when calling
+   * archive_read_data(), so be it. We'll do the same check there
+   * as well.
+   */
+  if (rar->has_encrypted_entries == ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW) {
+	  rar->has_encrypted_entries = 0;
+  }
+
   /* RAR files can be generated without EOF headers, so return ARCHIVE_EOF if
   * this fails.
   */
@@ -857,9 +904,14 @@ archive_read_format_rar_read_header(struct archive_read *a,
                             sizeof(rar->reserved2));
       }
 
+      /* Main header is password encrytped, so we cannot read any
+         file names or any other info about files from the header. */
       if (rar->main_flags & MHD_PASSWORD)
       {
-        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+        archive_entry_set_is_metadata_encrypted(entry, 1);
+        archive_entry_set_is_data_encrypted(entry, 1);
+        rar->has_encrypted_entries = 1;
+         archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                           "RAR encryption support unavailable.");
         return (ARCHIVE_FATAL);
       }
@@ -938,6 +990,10 @@ archive_read_format_rar_read_data(struct archive_read *a, const void **buff,
   struct rar *rar = (struct rar *)(a->format->data);
   int ret;
 
+  if (rar->has_encrypted_entries == ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW) {
+	  rar->has_encrypted_entries = 0;
+  }
+
   if (rar->bytes_unconsumed > 0) {
       /* Consume as much as the decompressor actually used. */
       __archive_read_consume(a, rar->bytes_unconsumed);
@@ -957,7 +1013,7 @@ archive_read_format_rar_read_data(struct archive_read *a, const void **buff,
   {
   case COMPRESS_METHOD_STORE:
     ret = read_data_stored(a, buff, size, offset);
-    break; 
+    break;
 
   case COMPRESS_METHOD_FASTEST:
   case COMPRESS_METHOD_FAST:
@@ -967,13 +1023,13 @@ archive_read_format_rar_read_data(struct archive_read *a, const void **buff,
     ret = read_data_compressed(a, buff, size, offset);
     if (ret != ARCHIVE_OK && ret != ARCHIVE_WARN)
       __archive_ppmd7_functions.Ppmd7_Free(&rar->ppmd7_context, &g_szalloc);
-    break; 
+    break;
 
   default:
     archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                       "Unsupported compression method for RAR file.");
     ret = ARCHIVE_FATAL;
-    break; 
+    break;
   }
   return (ret);
 }
@@ -1290,9 +1346,14 @@ read_header(struct archive_read *a, struct archive_entry *entry,
 
   if (rar->file_flags & FHD_PASSWORD)
   {
+	archive_entry_set_is_data_encrypted(entry, 1);
+	rar->has_encrypted_entries = 1;
     archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                       "RAR encryption support unavailable.");
-    return (ARCHIVE_FATAL);
+    /* Since it is only the data part itself that is encrypted we can at least
+       extract information about the currently processed entry and don't need
+       to return ARCHIVE_FATAL here. */
+    /*return (ARCHIVE_FATAL);*/
   }
 
   if (rar->file_flags & FHD_LARGE)
@@ -1377,7 +1438,7 @@ read_header(struct archive_read *a, struct archive_entry *entry,
           flagbyte = *(p + offset++);
           flagbits = 8;
         }
-	
+
         flagbits -= 2;
         switch((flagbyte >> flagbits) & 3)
         {
@@ -2611,7 +2672,7 @@ expand(struct archive_read *a, int64_t end)
     if ((symbol = read_next_symbol(a, &rar->maincode)) < 0)
       return (ARCHIVE_FATAL);
     rar->output_last_match = 0;
-    
+
     if (symbol < 256)
     {
       lzss_emit_literal(rar, symbol);