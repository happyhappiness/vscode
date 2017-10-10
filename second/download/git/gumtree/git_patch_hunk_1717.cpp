 	if (errstr) {
 		error("%s", errstr);
 		usage_with_options(hash_object_usage, hash_object_options);
 	}
 
 	if (hashstdin)
-		hash_fd(0, type, write_object, vpath);
+		hash_fd(0, type, vpath, flags, literally);
 
 	for (i = 0 ; i < argc; i++) {
 		const char *arg = argv[i];
 
 		if (0 <= prefix_length)
 			arg = prefix_filename(prefix, prefix_length, arg);
-		hash_object(arg, type, write_object,
-			    no_filters ? NULL : vpath ? vpath : arg);
+		hash_object(arg, type, no_filters ? NULL : vpath ? vpath : arg,
+			    flags, literally);
 	}
 
 	if (stdin_paths)
-		hash_stdin_paths(type, write_object);
+		hash_stdin_paths(type, no_filters, flags, literally);
 
 	return 0;
 }
