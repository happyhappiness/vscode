 	if (path && *path) 
 		args[argc++] = path;
 
 	args[argc] = NULL;
 
 	if (verbose > 3) {
-		fprintf(FINFO,"cmd=");
+		rprintf(FINFO,"cmd=");
 		for (i=0;i<argc;i++)
-			fprintf(FINFO,"%s ",args[i]);
-		fprintf(FINFO,"\n");
+			rprintf(FINFO,"%s ",args[i]);
+		rprintf(FINFO,"\n");
 	}
 
 	if (local_server) {
 		ret = local_child(argc, args, f_in, f_out);
 	} else {
 		ret = piped_child(args,f_in,f_out);
