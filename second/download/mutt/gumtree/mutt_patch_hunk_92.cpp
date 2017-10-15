 	pfx = NULL;
 
 	for(i = 2; i < argc; ) {
 		if(!strcmp(argv[i], "--")) {
 			i += 2;
 			if(i > argc) {
-				fprintf(stderr, "Command line usage: %s [flags] -- prefix [recipients]\n", argv[0]);
-				return 1;
+				print_usage(argv[0]);
 			}
 			pfx = argv[i-1];
 		}
 		if(pfx)
 			*opt++ = pfx;
 		*opt++ = argv[i++];
