 		int result;
 		FILE *fp;
 		char *filename;
 
 		if (argc != 5)
 			return error("fetch-native-store takes 3 args");
-		filename = git_path("FETCH_HEAD");
+		filename = git_path_fetch_head();
 		fp = fopen(filename, "a");
 		if (!fp)
 			return error("cannot open %s: %s", filename, strerror(errno));
 		result = fetch_native_store(fp, argv[2], argv[3], argv[4],
 					    verbose, force);
 		fclose(fp);
