@@ -136,7 +136,7 @@
 #define MAX_SYMBOLS       20
 
 /*
- * Considering L1,L2 cache miss and a calling of write sytem-call,
+ * Considering L1,L2 cache miss and a calling of write system-call,
  * the best size of the output buffer(uncompressed buffer) is 128K.
  * If the structure of extracting process is changed, this value
  * might be researched again.
@@ -199,6 +199,13 @@ struct lzss
   int64_t position;
 };
 
+struct data_block_offsets
+{
+  int64_t header_size;
+  int64_t start_offset;
+  int64_t end_offset;
+};
+
 struct rar
 {
   /* Entries from main RAR header */
@@ -217,6 +224,7 @@ struct rar
   long mnsec;
   mode_t mode;
   char *filename;
+  char *filename_save;
   size_t filename_allocated;
 
   /* File header optional entries */
@@ -234,6 +242,7 @@ struct rar
   int64_t bytes_uncopied;
   int64_t offset;
   int64_t offset_outgoing;
+  int64_t offset_seek;
   char valid;
   unsigned int unp_offset;
   unsigned int unp_buffer_size;
@@ -243,6 +252,10 @@ struct rar
   char entry_eof;
   unsigned long crc_calculated;
   int found_first_header;
+  char has_endarc_header;
+  struct data_block_offsets *dbo;
+  unsigned int cursor;
+  unsigned int nodes;
 
   /* LZSS members */
   struct huffman_code maincode;
@@ -301,11 +314,13 @@ static int archive_read_format_rar_read_header(struct archive_read *,
 static int archive_read_format_rar_read_data(struct archive_read *,
     const void **, size_t *, int64_t *);
 static int archive_read_format_rar_read_data_skip(struct archive_read *a);
+static int64_t archive_read_format_rar_seek_data(struct archive_read *, int64_t,
+    int);
 static int archive_read_format_rar_cleanup(struct archive_read *);
 
 /* Support functions */
 static int read_header(struct archive_read *, struct archive_entry *, char);
-static time_t get_time(int time);
+static time_t get_time(int);
 static int read_exttime(const char *, struct rar *, const char *);
 static int read_symlink_stored(struct archive_read *, struct archive_entry *,
                                struct archive_string_conv *);
@@ -328,6 +343,7 @@ static int make_table_recurse(struct archive_read *, struct huffman_code *, int,
 static int64_t expand(struct archive_read *, int64_t);
 static int copy_from_lzss_window(struct archive_read *, const void **,
                                    int64_t, int);
+static const void *rar_read_ahead(struct archive_read *, size_t, ssize_t *);
 
 /*
  * Bit stream reader.
@@ -449,11 +465,9 @@ rar_br_fillup(struct archive_read *a, struct rar_br *br)
         __archive_read_consume(a, rar->bytes_unconsumed);
         rar->bytes_unconsumed = 0;
       }
-      br->next_in = __archive_read_ahead(a, 1, &(br->avail_in));
+      br->next_in = rar_read_ahead(a, 1, &(br->avail_in));
       if (br->next_in == NULL)
         return (0);
-      if (br->avail_in > rar->bytes_remaining)
-        br->avail_in = rar->bytes_remaining;
       if (br->avail_in == 0)
         return (0);
     }
@@ -473,15 +487,13 @@ rar_br_preparation(struct archive_read *a, struct rar_br *br)
   struct rar *rar = (struct rar *)(a->format->data);
 
   if (rar->bytes_remaining > 0) {
-    br->next_in = __archive_read_ahead(a, 1, &(br->avail_in));
+    br->next_in = rar_read_ahead(a, 1, &(br->avail_in));
     if (br->next_in == NULL) {
       archive_set_error(&a->archive,
           ARCHIVE_ERRNO_FILE_FORMAT,
           "Truncated RAR file data");
       return (ARCHIVE_FATAL);
     }
-    if (br->avail_in > rar->bytes_remaining)
-      br->avail_in = rar->bytes_remaining;
     if (br->cache_avail == 0)
       (void)rar_br_fillup(a, br);
   }
@@ -522,7 +534,7 @@ lzss_size(struct lzss *lzss)
 static inline int
 lzss_offset_for_position(struct lzss *lzss, int64_t pos)
 {
-  return pos & lzss->mask;
+  return (int)(pos & lzss->mask);
 }
 
 static inline unsigned char *
@@ -642,6 +654,7 @@ archive_read_support_format_rar(struct archive *_a)
                                      archive_read_format_rar_read_header,
                                      archive_read_format_rar_read_data,
                                      archive_read_format_rar_read_data_skip,
+                                     archive_read_format_rar_seek_data,
                                      archive_read_format_rar_cleanup);
 
   if (r != ARCHIVE_OK)
@@ -757,11 +770,13 @@ archive_read_format_rar_options(struct archive_read *a,
       else
         ret = ARCHIVE_FATAL;
     }
-  } else
-    archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
-        "rar: unknown keyword ``%s''", key);
-                
-  return (ret);
+    return (ret);
+  }
+
+  /* Note: The "warn" return is just to inform the options
+   * supervisor that we didn't handle it.  It will generate
+   * a suitable error if no one used this option. */
+  return (ARCHIVE_WARN);
 }
 
 static int
@@ -842,21 +857,14 @@ archive_read_format_rar_read_header(struct archive_read *a,
                             sizeof(rar->reserved2));
       }
 
-      if (rar->main_flags & MHD_VOLUME ||
-          rar->main_flags & MHD_FIRSTVOLUME)
-      {
-        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
-                          "RAR volume support unavailable.");
-        return (ARCHIVE_FATAL);
-      }
       if (rar->main_flags & MHD_PASSWORD)
       {
         archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                           "RAR encryption support unavailable.");
         return (ARCHIVE_FATAL);
       }
 
-      crc32_val = crc32(0, (const unsigned char *)p + 2, skip - 2);
+      crc32_val = crc32(0, (const unsigned char *)p + 2, (unsigned)skip - 2);
       if ((crc32_val & 0xffff) != archive_le16dec(p)) {
         archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
           "Header CRC error");
@@ -873,6 +881,7 @@ archive_read_format_rar_read_header(struct archive_read *a,
     case SUB_HEAD:
     case PROTECT_HEAD:
     case SIGN_HEAD:
+    case ENDARC_HEAD:
       flags = archive_le16dec(p + 3);
       skip = archive_le16dec(p + 5);
       if (skip < 7) {
@@ -898,23 +907,22 @@ archive_read_format_rar_read_header(struct archive_read *a,
         p = h;
       }
 
-      crc32_val = crc32(0, (const unsigned char *)p + 2, skip - 2);
+      crc32_val = crc32(0, (const unsigned char *)p + 2, (unsigned)skip - 2);
       if ((crc32_val & 0xffff) != archive_le16dec(p)) {
         archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
           "Header CRC error");
         return (ARCHIVE_FATAL);
       }
       __archive_read_consume(a, skip);
+      if (head_type == ENDARC_HEAD)
+        return (ARCHIVE_EOF);
       break;
 
     case NEWSUB_HEAD:
       if ((ret = read_header(a, entry, head_type)) < ARCHIVE_WARN)
         return ret;
       break;
 
-    case ENDARC_HEAD:
-      return (ARCHIVE_EOF);
-
     default:
       archive_set_error(&a->archive,  ARCHIVE_ERRNO_FILE_FORMAT,
                         "Bad RAR file");
@@ -936,10 +944,12 @@ archive_read_format_rar_read_data(struct archive_read *a, const void **buff,
       rar->bytes_unconsumed = 0;
   }
 
-  if (rar->entry_eof) {
+  if (rar->entry_eof || rar->offset_seek >= rar->unp_size) {
     *buff = NULL;
     *size = 0;
     *offset = rar->offset;
+    if (*offset < rar->unp_size)
+      *offset = rar->unp_size;
     return (ARCHIVE_EOF);
   }
 
@@ -973,6 +983,7 @@ archive_read_format_rar_read_data_skip(struct archive_read *a)
 {
   struct rar *rar;
   int64_t bytes_skipped;
+  int ret;
 
   rar = (struct rar *)(a->format->data);
 
@@ -987,9 +998,179 @@ archive_read_format_rar_read_data_skip(struct archive_read *a)
     if (bytes_skipped < 0)
       return (ARCHIVE_FATAL);
   }
+
+  /* Compressed data to skip must be read from each header in a multivolume
+   * archive.
+   */
+  if (rar->main_flags & MHD_VOLUME && rar->file_flags & FHD_SPLIT_AFTER)
+  {
+    ret = archive_read_format_rar_read_header(a, a->entry);
+    if (ret == (ARCHIVE_EOF))
+      ret = archive_read_format_rar_read_header(a, a->entry);
+    if (ret != (ARCHIVE_OK))
+      return ret;
+    return archive_read_format_rar_read_data_skip(a);
+  }
+
   return (ARCHIVE_OK);
 }
 
+static int64_t
+archive_read_format_rar_seek_data(struct archive_read *a, int64_t offset,
+    int whence)
+{
+  int64_t client_offset, ret;
+  unsigned int i;
+  struct rar *rar = (struct rar *)(a->format->data);
+
+  if (rar->compression_method == COMPRESS_METHOD_STORE)
+  {
+    /* Modify the offset for use with SEEK_SET */
+    switch (whence)
+    {
+      case SEEK_CUR:
+        client_offset = rar->offset_seek;
+        break;
+      case SEEK_END:
+        client_offset = rar->unp_size;
+        break;
+      case SEEK_SET:
+      default:
+        client_offset = 0;
+    }
+    client_offset += offset;
+    if (client_offset < 0)
+    {
+      /* Can't seek past beginning of data block */
+      return -1;
+    }
+    else if (client_offset > rar->unp_size)
+    {
+      /*
+       * Set the returned offset but only seek to the end of
+       * the data block.
+       */
+      rar->offset_seek = client_offset;
+      client_offset = rar->unp_size;
+    }
+
+    client_offset += rar->dbo[0].start_offset;
+    i = 0;
+    while (i < rar->cursor)
+    {
+      i++;
+      client_offset += rar->dbo[i].start_offset - rar->dbo[i-1].end_offset;
+    }
+    if (rar->main_flags & MHD_VOLUME)
+    {
+      /* Find the appropriate offset among the multivolume archive */
+      while (1)
+      {
+        if (client_offset < rar->dbo[rar->cursor].start_offset &&
+          rar->file_flags & FHD_SPLIT_BEFORE)
+        {
+          /* Search backwards for the correct data block */
+          if (rar->cursor == 0)
+          {
+            archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+              "Attempt to seek past beginning of RAR data block");
+            return (ARCHIVE_FAILED);
+          }
+          rar->cursor--;
+          client_offset -= rar->dbo[rar->cursor+1].start_offset -
+            rar->dbo[rar->cursor].end_offset;
+          if (client_offset < rar->dbo[rar->cursor].start_offset)
+            continue;
+          ret = __archive_read_seek(a, rar->dbo[rar->cursor].start_offset -
+            rar->dbo[rar->cursor].header_size, SEEK_SET);
+          if (ret < (ARCHIVE_OK))
+            return ret;
+          ret = archive_read_format_rar_read_header(a, a->entry);
+          if (ret != (ARCHIVE_OK))
+          {
+            archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+              "Error during seek of RAR file");
+            return (ARCHIVE_FAILED);
+          }
+          rar->cursor--;
+          break;
+        }
+        else if (client_offset > rar->dbo[rar->cursor].end_offset &&
+          rar->file_flags & FHD_SPLIT_AFTER)
+        {
+          /* Search forward for the correct data block */
+          rar->cursor++;
+          if (rar->cursor < rar->nodes &&
+            client_offset > rar->dbo[rar->cursor].end_offset)
+          {
+            client_offset += rar->dbo[rar->cursor].start_offset -
+              rar->dbo[rar->cursor-1].end_offset;
+            continue;
+          }
+          rar->cursor--;
+          ret = __archive_read_seek(a, rar->dbo[rar->cursor].end_offset,
+                                    SEEK_SET);
+          if (ret < (ARCHIVE_OK))
+            return ret;
+          ret = archive_read_format_rar_read_header(a, a->entry);
+          if (ret == (ARCHIVE_EOF))
+          {
+            rar->has_endarc_header = 1;
+            ret = archive_read_format_rar_read_header(a, a->entry);
+          }
+          if (ret != (ARCHIVE_OK))
+          {
+            archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+              "Error during seek of RAR file");
+            return (ARCHIVE_FAILED);
+          }
+          client_offset += rar->dbo[rar->cursor].start_offset -
+            rar->dbo[rar->cursor-1].end_offset;
+          continue;
+        }
+        break;
+      }
+    }
+
+    ret = __archive_read_seek(a, client_offset, SEEK_SET);
+    if (ret < (ARCHIVE_OK))
+      return ret;
+    rar->bytes_remaining = rar->dbo[rar->cursor].end_offset - ret;
+    i = rar->cursor;
+    while (i > 0)
+    {
+      i--;
+      ret -= rar->dbo[i+1].start_offset - rar->dbo[i].end_offset;
+    }
+    ret -= rar->dbo[0].start_offset;
+
+    /* Always restart reading the file after a seek */
+    a->read_data_block = NULL;
+    a->read_data_offset = 0;
+    a->read_data_output_offset = 0;
+    a->read_data_remaining = 0;
+    rar->bytes_unconsumed = 0;
+    rar->offset = 0;
+
+    /*
+     * If a seek past the end of file was requested, return the requested
+     * offset.
+     */
+    if (ret == rar->unp_size && rar->offset_seek > rar->unp_size)
+      return rar->offset_seek;
+
+    /* Return the new offset */
+    rar->offset_seek = ret;
+    return rar->offset_seek;
+  }
+  else
+  {
+    archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
+      "Seeking of compressed RAR files is unsupported");
+  }
+  return (ARCHIVE_FAILED);
+}
+
 static int
 archive_read_format_rar_cleanup(struct archive_read *a)
 {
@@ -998,6 +1179,8 @@ archive_read_format_rar_cleanup(struct archive_read *a)
   rar = (struct rar *)(a->format->data);
   free_codes(a);
   free(rar->filename);
+  free(rar->filename_save);
+  free(rar->dbo);
   free(rar->unp_buffer);
   free(rar->lzss.window);
   __archive_ppmd7_functions.Ppmd7_Free(&rar->ppmd7_context, &g_szalloc);
@@ -1021,7 +1204,7 @@ read_header(struct archive_read *a, struct archive_entry *entry,
   char *strp;
   char packed_size[8];
   char unp_size[8];
-  int time;
+  int ttime;
   struct archive_string_conv *sconv, *fn_sconv;
   unsigned long crc32_val;
   int ret = (ARCHIVE_OK), ret2;
@@ -1047,7 +1230,7 @@ read_header(struct archive_read *a, struct archive_entry *entry,
   memcpy(&rar_header, p, sizeof(rar_header));
   rar->file_flags = archive_le16dec(rar_header.flags);
   header_size = archive_le16dec(rar_header.size);
-  if (header_size < sizeof(file_header) + 7) {
+  if (header_size < (int64_t)sizeof(file_header) + 7) {
     archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
       "Invalid header size");
     return (ARCHIVE_FATAL);
@@ -1082,11 +1265,11 @@ read_header(struct archive_read *a, struct archive_entry *entry,
     return (ARCHIVE_FATAL);
   }
 
-  if ((h = __archive_read_ahead(a, header_size - 7, NULL)) == NULL)
+  if ((h = __archive_read_ahead(a, (size_t)header_size - 7, NULL)) == NULL)
     return (ARCHIVE_FATAL);
 
   /* File Header CRC check. */
-  crc32_val = crc32(crc32_val, h, header_size - 7);
+  crc32_val = crc32(crc32_val, h, (unsigned)(header_size - 7));
   if ((crc32_val & 0xffff) != archive_le16dec(rar_header.crc)) {
     archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
       "Header CRC error");
@@ -1100,8 +1283,8 @@ read_header(struct archive_read *a, struct archive_entry *entry,
 
   rar->compression_method = file_header.method;
 
-  time = archive_le32dec(file_header.file_time);
-  rar->mtime = get_time(time);
+  ttime = archive_le32dec(file_header.file_time);
+  rar->mtime = get_time(ttime);
 
   rar->file_crc = archive_le32dec(file_header.file_crc);
 
@@ -1129,24 +1312,23 @@ read_header(struct archive_read *a, struct archive_entry *entry,
     rar->unp_size = archive_le32dec(file_header.unp_size);
   }
 
-  /* TODO: Need to use CRC check for these kind of cases.
-   * For now, check if sizes are not < 0.
-   */
   if (rar->packed_size < 0 || rar->unp_size < 0)
   {
     archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                       "Invalid sizes specified.");
     return (ARCHIVE_FATAL);
   }
 
+  rar->bytes_remaining = rar->packed_size;
+
   /* TODO: RARv3 subblocks contain comments. For now the complete block is
    * consumed at the end.
    */
   if (head_type == NEWSUB_HEAD) {
     size_t distance = p - (const char *)h;
     header_size += rar->packed_size;
     /* Make sure we have the extended data. */
-    if ((h = __archive_read_ahead(a, header_size - 7, NULL)) == NULL)
+    if ((h = __archive_read_ahead(a, (size_t)header_size - 7, NULL)) == NULL)
         return (ARCHIVE_FATAL);
     p = h;
     endp = p + header_size - 7;
@@ -1159,13 +1341,17 @@ read_header(struct archive_read *a, struct archive_entry *entry,
       "Invalid filename size");
     return (ARCHIVE_FATAL);
   }
-  if (rar->filename_allocated < filename_size+2) {
-    rar->filename = realloc(rar->filename, filename_size+2);
-    if (rar->filename == NULL) {
+  if (rar->filename_allocated < filename_size * 2 + 2) {
+    char *newptr;
+    size_t newsize = filename_size * 2 + 2;
+    newptr = realloc(rar->filename, newsize);
+    if (newptr == NULL) {
       archive_set_error(&a->archive, ENOMEM,
                         "Couldn't allocate memory.");
       return (ARCHIVE_FATAL);
     }
+    rar->filename = newptr;
+    rar->filename_allocated = newsize;
   }
   filename = rar->filename;
   memcpy(filename, p, filename_size);
@@ -1174,15 +1360,17 @@ read_header(struct archive_read *a, struct archive_entry *entry,
   {
     if (filename_size != strlen(filename))
     {
-      unsigned char highbyte, flagbits, flagbyte, length, offset;
+      unsigned char highbyte, flagbits, flagbyte;
+      unsigned fn_end, offset;
 
       end = filename_size;
+      fn_end = filename_size * 2;
       filename_size = 0;
-      offset = strlen(filename) + 1;
+      offset = (unsigned)strlen(filename) + 1;
       highbyte = *(p + offset++);
       flagbits = 0;
       flagbyte = 0;
-      while (offset < end && filename_size < end)
+      while (offset < end && filename_size < fn_end)
       {
         if (!flagbits)
         {
@@ -1208,19 +1396,26 @@ read_header(struct archive_read *a, struct archive_entry *entry,
             break;
           case 3:
           {
-            length = *(p + offset++);
-            while (length)
-            {
-	          if (filename_size >= end)
-			    break;
-              filename[filename_size++] = *(p + offset);
+            char extra, high;
+            uint8_t length = *(p + offset++);
+
+            if (length & 0x80) {
+              extra = *(p + offset++);
+              high = (char)highbyte;
+            } else
+              extra = high = 0;
+            length = (length & 0x7f) + 2;
+            while (length && filename_size < fn_end) {
+              unsigned cp = filename_size >> 1;
+              filename[filename_size++] = high;
+              filename[filename_size++] = p[cp] + extra;
               length--;
             }
           }
           break;
         }
       }
-      if (filename_size >= end) {
+      if (filename_size > fn_end) {
         archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
           "Invalid filename");
         return (ARCHIVE_FATAL);
@@ -1272,6 +1467,51 @@ read_header(struct archive_read *a, struct archive_entry *entry,
     p += filename_size;
   }
 
+  /* Split file in multivolume RAR. No more need to process header. */
+  if (rar->filename_save &&
+    !memcmp(rar->filename, rar->filename_save, filename_size + 1))
+  {
+    __archive_read_consume(a, header_size - 7);
+    rar->cursor++;
+    if (rar->cursor >= rar->nodes)
+    {
+      rar->nodes++;
+      if ((rar->dbo =
+        realloc(rar->dbo, sizeof(*rar->dbo) * rar->nodes)) == NULL)
+      {
+        archive_set_error(&a->archive, ENOMEM, "Couldn't allocate memory.");
+        return (ARCHIVE_FATAL);
+      }
+      rar->dbo[rar->cursor].header_size = header_size;
+      rar->dbo[rar->cursor].start_offset = -1;
+      rar->dbo[rar->cursor].end_offset = -1;
+    }
+    if (rar->dbo[rar->cursor].start_offset < 0)
+    {
+      rar->dbo[rar->cursor].start_offset = a->filter->position;
+      rar->dbo[rar->cursor].end_offset = rar->dbo[rar->cursor].start_offset +
+        rar->packed_size;
+    }
+    return ret;
+  }
+
+  rar->filename_save = (char*)realloc(rar->filename_save,
+                                      filename_size + 1);
+  memcpy(rar->filename_save, rar->filename, filename_size + 1);
+
+  /* Set info for seeking */
+  free(rar->dbo);
+  if ((rar->dbo = calloc(1, sizeof(*rar->dbo))) == NULL)
+  {
+    archive_set_error(&a->archive, ENOMEM, "Couldn't allocate memory.");
+    return (ARCHIVE_FATAL);
+  }
+  rar->dbo[0].header_size = header_size;
+  rar->dbo[0].start_offset = -1;
+  rar->dbo[0].end_offset = -1;
+  rar->cursor = 0;
+  rar->nodes = 1;
+
   if (rar->file_flags & FHD_SALT)
   {
     if (p + 8 > endp) {
@@ -1292,6 +1532,8 @@ read_header(struct archive_read *a, struct archive_entry *entry,
   }
 
   __archive_read_consume(a, header_size - 7);
+  rar->dbo[0].start_offset = a->filter->position;
+  rar->dbo[0].end_offset = rar->dbo[0].start_offset + rar->packed_size;
 
   switch(file_header.host_os)
   {
@@ -1318,9 +1560,10 @@ read_header(struct archive_read *a, struct archive_entry *entry,
     return (ARCHIVE_FATAL);
   }
 
-  rar->bytes_remaining = rar->packed_size;
   rar->bytes_uncopied = rar->bytes_unconsumed = 0;
-  rar->lzss.position = rar->dictionary_size = rar->offset = 0;
+  rar->lzss.position = rar->offset = 0;
+  rar->offset_seek = 0;
+  rar->dictionary_size = 0;
   rar->offset_outgoing = 0;
   rar->br.cache_avail = 0;
   rar->br.avail_in = 0;
@@ -1381,15 +1624,15 @@ read_header(struct archive_read *a, struct archive_entry *entry,
 }
 
 static time_t
-get_time(int time)
+get_time(int ttime)
 {
   struct tm tm;
-  tm.tm_sec = 2 * (time & 0x1f);
-  tm.tm_min = (time >> 5) & 0x3f;
-  tm.tm_hour = (time >> 11) & 0x1f;
-  tm.tm_mday = (time >> 16) & 0x1f;
-  tm.tm_mon = ((time >> 21) & 0x0f) - 1;
-  tm.tm_year = ((time >> 25) & 0x7f) + 80;
+  tm.tm_sec = 2 * (ttime & 0x1f);
+  tm.tm_min = (ttime >> 5) & 0x3f;
+  tm.tm_hour = (ttime >> 11) & 0x1f;
+  tm.tm_mday = (ttime >> 16) & 0x1f;
+  tm.tm_mon = ((ttime >> 21) & 0x0f) - 1;
+  tm.tm_year = ((ttime >> 25) & 0x7f) + 80;
   tm.tm_isdst = -1;
   return mktime(&tm);
 }
@@ -1398,7 +1641,7 @@ static int
 read_exttime(const char *p, struct rar *rar, const char *endp)
 {
   unsigned rmode, flags, rem, j, count;
-  int time, i;
+  int ttime, i;
   struct tm *tm;
   time_t t;
   long nsec;
@@ -1420,8 +1663,8 @@ read_exttime(const char *p, struct rar *rar, const char *endp)
       {
         if (p + 4 > endp)
           return (-1);
-        time = archive_le32dec(p);
-        t = get_time(time);
+        ttime = archive_le32dec(p);
+        t = get_time(ttime);
         p += 4;
       }
       rem = 0;
@@ -1475,11 +1718,12 @@ read_symlink_stored(struct archive_read *a, struct archive_entry *entry,
   int ret = (ARCHIVE_OK);
 
   rar = (struct rar *)(a->format->data);
-  if ((h = __archive_read_ahead(a, rar->packed_size, NULL)) == NULL)
+  if ((h = rar_read_ahead(a, (size_t)rar->packed_size, NULL)) == NULL)
     return (ARCHIVE_FATAL);
   p = h;
 
-  if (archive_entry_copy_symlink_l(entry, p, rar->packed_size, sconv))
+  if (archive_entry_copy_symlink_l(entry,
+      p, (size_t)rar->packed_size, sconv))
   {
     if (errno == ENOMEM)
     {
@@ -1504,7 +1748,8 @@ read_data_stored(struct archive_read *a, const void **buff, size_t *size,
   ssize_t bytes_avail;
 
   rar = (struct rar *)(a->format->data);
-  if (rar->bytes_remaining == 0)
+  if (rar->bytes_remaining == 0 &&
+    !(rar->main_flags & MHD_VOLUME && rar->file_flags & FHD_SPLIT_AFTER))
   {
     *buff = NULL;
     *size = 0;
@@ -1518,23 +1763,23 @@ read_data_stored(struct archive_read *a, const void **buff, size_t *size,
     return (ARCHIVE_EOF);
   }
 
-  *buff = __archive_read_ahead(a, 1, &bytes_avail);
+  *buff = rar_read_ahead(a, 1, &bytes_avail);
   if (bytes_avail <= 0)
   {
     archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                       "Truncated RAR file data");
     return (ARCHIVE_FATAL);
   }
-  if (bytes_avail > rar->bytes_remaining)
-    bytes_avail = rar->bytes_remaining;
 
   *size = bytes_avail;
   *offset = rar->offset;
   rar->offset += bytes_avail;
+  rar->offset_seek += bytes_avail;
   rar->bytes_remaining -= bytes_avail;
   rar->bytes_unconsumed = bytes_avail;
   /* Calculate File CRC. */
-  rar->crc_calculated = crc32(rar->crc_calculated, *buff, bytes_avail);
+  rar->crc_calculated = crc32(rar->crc_calculated, *buff,
+    (unsigned)bytes_avail);
   return (ARCHIVE_OK);
 }
 
@@ -1564,7 +1809,8 @@ read_data_compressed(struct archive_read *a, const void **buff, size_t *size,
         *offset = rar->offset_outgoing;
         rar->offset_outgoing += *size;
         /* Calculate File CRC. */
-        rar->crc_calculated = crc32(rar->crc_calculated, *buff, *size);
+        rar->crc_calculated = crc32(rar->crc_calculated, *buff,
+          (unsigned)*size);
         rar->unp_offset = 0;
         return (ARCHIVE_OK);
       }
@@ -1585,8 +1831,8 @@ read_data_compressed(struct archive_read *a, const void **buff, size_t *size,
       if (rar->bytes_uncopied > (rar->unp_buffer_size - rar->unp_offset))
         bs = rar->unp_buffer_size - rar->unp_offset;
       else
-        bs = rar->bytes_uncopied;
-      ret = copy_from_lzss_window(a, buff, rar->offset, bs);
+        bs = (size_t)rar->bytes_uncopied;
+      ret = copy_from_lzss_window(a, buff, rar->offset, (int)bs);
       if (ret != ARCHIVE_OK)
         return (ret);
       rar->offset += bs;
@@ -1597,7 +1843,8 @@ read_data_compressed(struct archive_read *a, const void **buff, size_t *size,
         *offset = rar->offset_outgoing;
         rar->offset_outgoing += *size;
         /* Calculate File CRC. */
-        rar->crc_calculated = crc32(rar->crc_calculated, *buff, *size);
+        rar->crc_calculated = crc32(rar->crc_calculated, *buff,
+          (unsigned)*size);
         return (ret);
       }
       continue;
@@ -1713,8 +1960,8 @@ read_data_compressed(struct archive_read *a, const void **buff, size_t *size,
     if (rar->bytes_uncopied > (rar->unp_buffer_size - rar->unp_offset))
       bs = rar->unp_buffer_size - rar->unp_offset;
     else
-      bs = rar->bytes_uncopied;
-    ret = copy_from_lzss_window(a, buff, rar->offset, bs);
+      bs = (size_t)rar->bytes_uncopied;
+    ret = copy_from_lzss_window(a, buff, rar->offset, (int)bs);
     if (ret != ARCHIVE_OK)
       return (ret);
     rar->offset += bs;
@@ -1730,7 +1977,7 @@ read_data_compressed(struct archive_read *a, const void **buff, size_t *size,
   *offset = rar->offset_outgoing;
   rar->offset_outgoing += *size;
   /* Calculate File CRC. */
-  rar->crc_calculated = crc32(rar->crc_calculated, *buff, *size);
+  rar->crc_calculated = crc32(rar->crc_calculated, *buff, (unsigned)*size);
   return ret;
 }
 
@@ -1973,17 +2220,21 @@ parse_codes(struct archive_read *a)
     /* Seems as though dictionary sizes are not used. Even so, minimize
      * memory usage as much as possible.
      */
+    void *new_window;
+    unsigned int new_size;
+
     if (rar->unp_size >= DICTIONARY_MAX_SIZE)
-      rar->dictionary_size = DICTIONARY_MAX_SIZE;
+      new_size = DICTIONARY_MAX_SIZE;
     else
-      rar->dictionary_size = rar_fls(rar->unp_size) << 1;
-    rar->lzss.window = (unsigned char *)realloc(rar->lzss.window,
-                                                rar->dictionary_size);
-    if (rar->lzss.window == NULL) {
+      new_size = rar_fls((unsigned int)rar->unp_size) << 1;
+    new_window = realloc(rar->lzss.window, new_size);
+    if (new_window == NULL) {
       archive_set_error(&a->archive, ENOMEM,
                         "Unable to allocate memory for uncompressed data.");
       return (ARCHIVE_FATAL);
     }
+    rar->lzss.window = (unsigned char *)new_window;
+    rar->dictionary_size = new_size;
     memset(rar->lzss.window, 0, rar->dictionary_size);
     rar->lzss.mask = rar->dictionary_size - 1;
   }
@@ -2221,10 +2472,12 @@ add_value(struct archive_read *a, struct huffman_code *code, int value,
 static int
 new_node(struct huffman_code *code)
 {
-  code->tree = (struct huffman_tree_node *)realloc(code->tree,
-    (code->numentries + 1) * sizeof(*code->tree));
-  if (code->tree == NULL)
+  void *new_tree;
+
+  new_tree = realloc(code->tree, (code->numentries + 1) * sizeof(*code->tree));
+  if (new_tree == NULL)
     return (-1);
+  code->tree = (struct huffman_tree_node *)new_tree;
   code->tree[code->numentries].branches[0] = -1;
   code->tree[code->numentries].branches[1] = -2;
   return 1;
@@ -2239,8 +2492,8 @@ make_table(struct archive_read *a, struct huffman_code *code)
     code->tablesize = code->maxlength;
 
   code->table =
-    (struct huffman_table_entry *)malloc(sizeof(*code->table)
-    * (1 << code->tablesize));
+    (struct huffman_table_entry *)calloc(1, sizeof(*code->table)
+    * ((size_t)1 << code->tablesize));
 
   return make_table_recurse(a, code, 0, code->table, 0, code->tablesize);
 }
@@ -2408,9 +2661,9 @@ expand(struct archive_read *a, int64_t end)
 
       if ((lensymbol = read_next_symbol(a, &rar->lengthcode)) < 0)
         goto bad_data;
-      if (lensymbol > sizeof(lengthbases)/sizeof(lengthbases[0]))
+      if (lensymbol > (int)(sizeof(lengthbases)/sizeof(lengthbases[0])))
         goto bad_data;
-      if (lensymbol > sizeof(lengthbits)/sizeof(lengthbits[0]))
+      if (lensymbol > (int)(sizeof(lengthbits)/sizeof(lengthbits[0])))
         goto bad_data;
       len = lengthbases[lensymbol] + 2;
       if (lengthbits[lensymbol] > 0) {
@@ -2442,9 +2695,9 @@ expand(struct archive_read *a, int64_t end)
     }
     else
     {
-      if (symbol-271 > sizeof(lengthbases)/sizeof(lengthbases[0]))
+      if (symbol-271 > (int)(sizeof(lengthbases)/sizeof(lengthbases[0])))
         goto bad_data;
-      if (symbol-271 > sizeof(lengthbits)/sizeof(lengthbits[0]))
+      if (symbol-271 > (int)(sizeof(lengthbits)/sizeof(lengthbits[0])))
         goto bad_data;
       len = lengthbases[symbol-271]+3;
       if(lengthbits[symbol-271] > 0) {
@@ -2456,9 +2709,9 @@ expand(struct archive_read *a, int64_t end)
 
       if ((offssymbol = read_next_symbol(a, &rar->offsetcode)) < 0)
         goto bad_data;
-      if (offssymbol > sizeof(offsetbases)/sizeof(offsetbases[0]))
+      if (offssymbol > (int)(sizeof(offsetbases)/sizeof(offsetbases[0])))
         goto bad_data;
-      if (offssymbol > sizeof(offsetbits)/sizeof(offsetbits[0]))
+      if (offssymbol > (int)(sizeof(offsetbits)/sizeof(offsetbits[0])))
         goto bad_data;
       offs = offsetbases[offssymbol]+1;
       if(offsetbits[offssymbol] > 0)
@@ -2572,3 +2825,34 @@ copy_from_lzss_window(struct archive_read *a, const void **buffer,
     *buffer = NULL;
   return (ARCHIVE_OK);
 }
+
+static const void *
+rar_read_ahead(struct archive_read *a, size_t min, ssize_t *avail)
+{
+  struct rar *rar = (struct rar *)(a->format->data);
+  const void *h = __archive_read_ahead(a, min, avail);
+  int ret;
+  if (avail)
+  {
+    if (a->read_data_is_posix_read && *avail > (ssize_t)a->read_data_requested)
+      *avail = a->read_data_requested;
+    if (*avail > rar->bytes_remaining)
+      *avail = (ssize_t)rar->bytes_remaining;
+    if (*avail < 0)
+      return NULL;
+    else if (*avail == 0 && rar->main_flags & MHD_VOLUME &&
+      rar->file_flags & FHD_SPLIT_AFTER)
+    {
+      ret = archive_read_format_rar_read_header(a, a->entry);
+      if (ret == (ARCHIVE_EOF))
+      {
+        rar->has_endarc_header = 1;
+        ret = archive_read_format_rar_read_header(a, a->entry);
+      }
+      if (ret != (ARCHIVE_OK))
+        return NULL;
+      return rar_read_ahead(a, min, avail);
+    }
+  }
+  return h;
+}