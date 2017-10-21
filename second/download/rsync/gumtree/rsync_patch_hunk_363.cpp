 
 	/* if protocol version is >= 17 then send the io_error flag */
 	if (f != -1 && remote_version >= 17) {
 		write_int(f, io_error);
 	}
 
+	if (verbose > 2)
+		fprintf(FINFO,"send_file_list done\n");
+
 	return flist;
 }
 
 
 struct file_list *recv_file_list(int f)
 {
