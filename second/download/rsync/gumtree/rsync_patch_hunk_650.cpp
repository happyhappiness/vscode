 
 	if (flags & LONG_NAME)
 		l2 = read_int(f);
 	else
 		l2 = read_byte(f);
 
-	file = (struct file_struct *) malloc(sizeof(*file));
+	file = new(struct file_struct);
 	if (!file)
 		out_of_memory("receive_file_entry");
 	memset((char *) file, 0, sizeof(*file));
 	(*fptr) = file;
 
 	if (l2 >= MAXPATHLEN - l1) {
