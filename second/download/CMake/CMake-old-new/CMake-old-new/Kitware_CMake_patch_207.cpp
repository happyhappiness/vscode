@@ -2127,6 +2127,12 @@ parse_codes(struct archive_read *a)
       rar->range_dec.Stream = &rar->bytein;
       __archive_ppmd7_functions.Ppmd7_Construct(&rar->ppmd7_context);
 
+      if (rar->dictionary_size == 0) {
+	      archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+                          "Invalid zero dictionary size");
+	      return (ARCHIVE_FATAL);
+      }
+
       if (!__archive_ppmd7_functions.Ppmd7_Alloc(&rar->ppmd7_context,
         rar->dictionary_size, &g_szalloc))
       {
@@ -2884,11 +2890,10 @@ copy_from_lzss_window(struct archive_read *a, const void **buffer,
   }
 
   windowoffs = lzss_offset_for_position(&rar->lzss, startpos);
-  if(windowoffs + length <= lzss_size(&rar->lzss))
+  if(windowoffs + length <= lzss_size(&rar->lzss)) {
     memcpy(&rar->unp_buffer[rar->unp_offset], &rar->lzss.window[windowoffs],
            length);
-  else
-  {
+  } else if (length <= lzss_size(&rar->lzss)) {
     firstpart = lzss_size(&rar->lzss) - windowoffs;
     if (firstpart < 0) {
       archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
@@ -2900,9 +2905,14 @@ copy_from_lzss_window(struct archive_read *a, const void **buffer,
              &rar->lzss.window[windowoffs], firstpart);
       memcpy(&rar->unp_buffer[rar->unp_offset + firstpart],
              &rar->lzss.window[0], length - firstpart);
-    } else
+    } else {
       memcpy(&rar->unp_buffer[rar->unp_offset],
              &rar->lzss.window[windowoffs], length);
+    }
+  } else {
+      archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
+                        "Bad RAR file data");
+      return (ARCHIVE_FATAL);
   }
   rar->unp_offset += length;
   if (rar->unp_offset >= rar->unp_buffer_size)