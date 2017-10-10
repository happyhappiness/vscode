  * If "raw" is true, then the object's raw contents are printed according to
  * "type". Otherwise, we pretty-print the contents for human editing.
  */
 static void export_object(const unsigned char *sha1, enum object_type type,
 			  int raw, const char *filename)
 {
-	struct child_process cmd = { NULL };
+	struct child_process cmd = CHILD_PROCESS_INIT;
 	int fd;
 
 	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
 	if (fd < 0)
 		die_errno("unable to open %s for writing", filename);
 
