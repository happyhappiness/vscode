@@ -647,13 +647,12 @@ archive_read_support_format_rar(struct archive *_a)
   archive_check_magic(_a, ARCHIVE_READ_MAGIC, ARCHIVE_STATE_NEW,
                       "archive_read_support_format_rar");
 
-  rar = (struct rar *)malloc(sizeof(*rar));
+  rar = (struct rar *)calloc(sizeof(*rar), 1);
   if (rar == NULL)
   {
     archive_set_error(&a->archive, ENOMEM, "Can't allocate rar data");
     return (ARCHIVE_FATAL);
   }
-  memset(rar, 0, sizeof(*rar));
 
 	/*
 	 * Until enough data has been read, we cannot tell about
@@ -907,7 +906,7 @@ archive_read_format_rar_read_header(struct archive_read *a,
                             sizeof(rar->reserved2));
       }
 
-      /* Main header is password encrytped, so we cannot read any
+      /* Main header is password encrypted, so we cannot read any
          file names or any other info about files from the header. */
       if (rar->main_flags & MHD_PASSWORD)
       {