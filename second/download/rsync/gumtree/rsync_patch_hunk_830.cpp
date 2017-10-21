 		*argv_ptr = argv;
 		*maxargs_ptr = maxargs;
 	}
 	if (globbuf.gl_pathc == 0)
 		argv[argc++] = s;
 	else {
-		int j = globbuf.gl_pathc;
+		int i;
 		free(s);
-		for (i = 0; i < j; i++) {
+		for (i = 0; i < (int)globbuf.gl_pathc; i++) {
 			if (!(argv[argc++] = strdup(globbuf.gl_pathv[i])))
 				out_of_memory("glob_expand_one");
 		}
 	}
 	globfree(&globbuf);
 #endif
