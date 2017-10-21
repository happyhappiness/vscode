 	    fprintf(FERROR,"ERROR: symbolic links not supported\n");
 	    exit_cleanup(1);
     }
 #endif
 
     if (am_server) {
-      setup_protocol(STDOUT_FILENO,STDIN_FILENO);
-	
-      if (sender) {
-	recv_exclude_list(STDIN_FILENO);
-	if (cvs_exclude)
-	  add_cvs_excludes();
-	do_server_sender(argc,argv);
-      } else {
-	do_server_recv(argc,argv);
-      }
-      exit_cleanup(0);
+	    start_server(argc, argv);
     }
 
     if (argc < 2) {
       usage(FERROR);
       exit_cleanup(1);
     }
 
     p = strchr(argv[0],':');
 
     if (p) {
-      sender = 0;
+      am_sender = 0;
       *p = 0;
       shell_machine = argv[0];
       shell_path = p+1;
       argc--;
       argv++;
     } else {
-      sender = 1;
+      am_sender = 1;
 
       p = strchr(argv[argc-1],':');
       if (!p) {
 	local_server = 1;
       }
 
