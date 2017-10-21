 	case 'B':
 	  block_size = atoi(optarg);
 	  break;
 
 	default:
 	  fprintf(stderr,"bad option -%c\n",opt);
-	  exit(1);
+	  exit_cleanup(1);
 	}
     }
 
     while (optind--) {
       argc--;
       argv++;
     }
 
+    signal(SIGCHLD,SIG_IGN);
+    signal(SIGINT,SIGNAL_CAST sig_int);
+    signal(SIGPIPE,SIGNAL_CAST sig_int);
+    signal(SIGHUP,SIGNAL_CAST sig_int);
+
     if (dry_run)
       verbose = MAX(verbose,1);
 
     if (am_server) {
       remote_version = read_int(STDIN_FILENO);
       if (remote_version < MIN_PROTOCOL_VERSION ||
 	  remote_version > MAX_PROTOCOL_VERSION) {
 	fprintf(stderr,"protocol version mismatch - is your shell clean?\n");
-	exit(1);
+	exit_cleanup(1);
       }
       write_int(STDOUT_FILENO,PROTOCOL_VERSION);
       write_flush(STDOUT_FILENO);
 
       setup_protocol();
 	
