@@ -186,6 +186,7 @@ struct huffman_code
 {
   struct huffman_tree_node *tree;
   int numentries;
+  int numallocatedentries;
   int minlength;
   int maxlength;
   int tablesize;
@@ -225,6 +226,7 @@ struct rar
   mode_t mode;
   char *filename;
   char *filename_save;
+  size_t filename_save_size;
   size_t filename_allocated;
 
   /* File header optional entries */
@@ -1000,8 +1002,8 @@ archive_read_format_rar_read_data(struct archive_read *a, const void **buff,
       rar->bytes_unconsumed = 0;
   }
 
+  *buff = NULL;
   if (rar->entry_eof || rar->offset_seek >= rar->unp_size) {
-    *buff = NULL;
     *size = 0;
     *offset = rar->offset;
     if (*offset < rar->unp_size)
@@ -1201,10 +1203,8 @@ archive_read_format_rar_seek_data(struct archive_read *a, int64_t offset,
     ret -= rar->dbo[0].start_offset;
 
     /* Always restart reading the file after a seek */
-    a->read_data_block = NULL;
-    a->read_data_offset = 0;
-    a->read_data_output_offset = 0;
-    a->read_data_remaining = 0;
+    __archive_reset_read_data(&a->archive);
+
     rar->bytes_unconsumed = 0;
     rar->offset = 0;
 
@@ -1530,6 +1530,7 @@ read_header(struct archive_read *a, struct archive_entry *entry,
 
   /* Split file in multivolume RAR. No more need to process header. */
   if (rar->filename_save &&
+    filename_size == rar->filename_save_size &&
     !memcmp(rar->filename, rar->filename_save, filename_size + 1))
   {
     __archive_read_consume(a, header_size - 7);
@@ -1559,6 +1560,7 @@ read_header(struct archive_read *a, struct archive_entry *entry,
   rar->filename_save = (char*)realloc(rar->filename_save,
                                       filename_size + 1);
   memcpy(rar->filename_save, rar->filename, filename_size + 1);
+  rar->filename_save_size = filename_size;
 
   /* Set info for seeking */
   free(rar->dbo);
@@ -2406,6 +2408,8 @@ create_code(struct archive_read *a, struct huffman_code *code,
 {
   int i, j, codebits = 0, symbolsleft = numsymbols;
 
+  code->numentries = 0;
+  code->numallocatedentries = 0;
   if (new_node(code) < 0) {
     archive_set_error(&a->archive, ENOMEM,
                       "Unable to allocate memory for node data.");
@@ -2534,11 +2538,17 @@ static int
 new_node(struct huffman_code *code)
 {
   void *new_tree;
-
-  new_tree = realloc(code->tree, (code->numentries + 1) * sizeof(*code->tree));
-  if (new_tree == NULL)
-    return (-1);
-  code->tree = (struct huffman_tree_node *)new_tree;
+  if (code->numallocatedentries == code->numentries) {
+    int new_num_entries = 256;
+    if (code->numentries > 0) {
+        new_num_entries = code->numentries * 2;
+    }
+    new_tree = realloc(code->tree, new_num_entries * sizeof(*code->tree));
+    if (new_tree == NULL)
+        return (-1);
+    code->tree = (struct huffman_tree_node *)new_tree;
+    code->numallocatedentries = new_num_entries;
+  }
   code->tree[code->numentries].branches[0] = -1;
   code->tree[code->numentries].branches[1] = -2;
   return 1;
@@ -2895,8 +2905,8 @@ rar_read_ahead(struct archive_read *a, size_t min, ssize_t *avail)
   int ret;
   if (avail)
   {
-    if (a->read_data_is_posix_read && *avail > (ssize_t)a->read_data_requested)
-      *avail = a->read_data_requested;
+    if (a->archive.read_data_is_posix_read && *avail > (ssize_t)a->archive.read_data_requested)
+      *avail = a->archive.read_data_requested;
     if (*avail > rar->bytes_remaining)
       *avail = (ssize_t)rar->bytes_remaining;
     if (*avail < 0)