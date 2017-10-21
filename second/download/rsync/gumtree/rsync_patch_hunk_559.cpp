 
 	file = (struct file_struct *)malloc(sizeof(*file));
 	if (!file) out_of_memory("receive_file_entry");
 	memset((char *)file, 0, sizeof(*file));
 	(*fptr) = file;
 
-	if (l2 >= MAXPATHLEN-l1) overflow("receive_file_entry");
+	if (l2 >= MAXPATHLEN-l1) {
+		rprintf(FERROR,"overflow: flags=0x%x l1=%d l2=%d lastname=%s\n",
+			flags, l1, l2, lastname);
+		overflow("receive_file_entry");
+	}
 
 	strlcpy(thisname,lastname,l1+1);
 	read_sbuf(f,&thisname[l1],l2);
 	thisname[l1+l2] = 0;
 
 	strlcpy(lastname,thisname,MAXPATHLEN);
