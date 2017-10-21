     if ((fd_file = open(*argv, O_WRONLY|O_TRUNC|O_CREAT|O_BINARY, 0644)) < 0) {
 	fprintf(stderr, "Unable to write to `%s': %s\n", *argv, strerror(errno));
 	exit(1);
     }
     set_blocking(fd_file);
 
-    signal(SIGPIPE, SIG_IGN);
+    SIGACTION(SIGPIPE, SIG_IGN);
 
     run_program(argv + 1);
 
 #if defined HAVE_SETMODE && O_BINARY
     setmode(STDIN_FILENO, O_BINARY);
     setmode(STDOUT_FILENO, O_BINARY);
