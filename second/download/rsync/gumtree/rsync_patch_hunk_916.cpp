 				out_of_memory("read_args");
 			argv[argc++] = p;
 			if (*p == '.' && p[1] == '\0')
 				dot_pos = argc;
 		}
 	}
+	argv[argc] = NULL;
+
+	glob_expand(NULL, NULL, NULL, NULL);
 
 	*argc_p = argc;
 	*argv_p = argv;
-
-	return dot_pos ? dot_pos : argc;
 }
 
 int io_start_buffering_out(int f_out)
 {
 	if (iobuf_out) {
 		assert(f_out == iobuf_f_out);
