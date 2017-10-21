 
 
 
 
 static char *get_local_name(struct file_list *flist,char *name)
 {
-  struct stat st;
+	STRUCT_STAT st;
+	extern int orig_umask;
 
-  if (stat(name,&st) == 0) {
+  if (do_stat(name,&st) == 0) {
     if (S_ISDIR(st.st_mode)) {
       if (chdir(name) != 0) {
-	fprintf(FERROR,"chdir %s : %s (1)\n",name,strerror(errno));
+	rprintf(FERROR,"chdir %s : %s (1)\n",name,strerror(errno));
 	exit_cleanup(1);
       }
       return NULL;
     }
     if (flist->count > 1) {
-      fprintf(FERROR,"ERROR: destination must be a directory when copying more than 1 file\n");
+      rprintf(FERROR,"ERROR: destination must be a directory when copying more than 1 file\n");
       exit_cleanup(1);
     }
     return name;
   }
 
   if (flist->count == 1)
     return name;
 
   if (!name) 
     return NULL;
 
   if (do_mkdir(name,0777 & ~orig_umask) != 0) {
-    fprintf(FERROR,"mkdir %s : %s (1)\n",name,strerror(errno));
+    rprintf(FERROR,"mkdir %s : %s (1)\n",name,strerror(errno));
     exit_cleanup(1);
   } else {
-    fprintf(FINFO,"created directory %s\n",name);
+    rprintf(FINFO,"created directory %s\n",name);
   }
 
   if (chdir(name) != 0) {
-    fprintf(FERROR,"chdir %s : %s (2)\n",name,strerror(errno));
+    rprintf(FERROR,"chdir %s : %s (2)\n",name,strerror(errno));
     exit_cleanup(1);
   }
 
   return NULL;
 }
 
 
 
 
-void do_server_sender(int argc,char *argv[])
+static void do_server_sender(int f_in, int f_out, int argc,char *argv[])
 {
-  int i;
-  struct file_list *flist;
-  char *dir = argv[0];
+	int i;
+	struct file_list *flist;
+	char *dir = argv[0];
+	extern int relative_paths;
+	extern int am_daemon;
+	extern int recurse;
 
-  if (verbose > 2)
-    fprintf(FINFO,"server_sender starting pid=%d\n",(int)getpid());
+	if (verbose > 2)
+		rprintf(FINFO,"server_sender starting pid=%d\n",(int)getpid());
   
-  if (!relative_paths && chdir(dir) != 0) {
-	  fprintf(FERROR,"chdir %s: %s (3)\n",dir,strerror(errno));
-	  exit_cleanup(1);
-  }
-  argc--;
-  argv++;
+	if (!relative_paths && chdir(dir) != 0) {
+		rprintf(FERROR,"chdir %s: %s (3)\n",dir,strerror(errno));
+		exit_cleanup(1);
+	}
+	argc--;
+	argv++;
   
-  if (strcmp(dir,".")) {
-	  int l = strlen(dir);
-	  if (strcmp(dir,"/") == 0) 
-		  l = 0;
-	  for (i=0;i<argc;i++)
-		  argv[i] += l+1;
-  }
-
-  if (argc == 0 && recurse) {
-	  argc=1;
-	  argv--;
-	  argv[0] = ".";
-  }
-    
+	if (strcmp(dir,".")) {
+		int l = strlen(dir);
+		if (strcmp(dir,"/") == 0) 
+			l = 0;
+		for (i=0;i<argc;i++)
+			argv[i] += l+1;
+	}
 
-  flist = send_file_list(STDOUT_FILENO,argc,argv);
-  send_files(flist,STDOUT_FILENO,STDIN_FILENO);
-  report(STDOUT_FILENO);
-  exit_cleanup(0);
+	if (argc == 0 && recurse) {
+		argc=1;
+		argv--;
+		argv[0] = ".";
+	}
+	
+	flist = send_file_list(f_out,argc,argv);
+	send_files(flist,f_out,f_in);
+	report(f_out);
+	exit_cleanup(0);
 }
 
 
 static int do_recv(int f_in,int f_out,struct file_list *flist,char *local_name)
 {
   int pid;
   int status=0;
   int recv_pipe[2];
+  extern int preserve_hard_links;
 
   if (preserve_hard_links)
     init_hard_links(flist);
 
   if (pipe(recv_pipe) < 0) {
-    fprintf(FERROR,"pipe failed in do_recv\n");
+    rprintf(FERROR,"pipe failed in do_recv\n");
     exit(1);
   }
   
 
   if ((pid=do_fork()) == 0) {
     recv_files(f_in,flist,local_name,recv_pipe[1]);
     if (verbose > 2)
-      fprintf(FINFO,"receiver read %ld\n",(long)read_total());
+      rprintf(FINFO,"receiver read %ld\n",(long)read_total());
     exit_cleanup(0);
   }
 
   generate_files(f_out,flist,local_name,recv_pipe[0]);
 
   waitpid(pid, &status, 0);
 
   return status;
 }
 
 
-void do_server_recv(int argc,char *argv[])
+static void do_server_recv(int f_in, int f_out, int argc,char *argv[])
 {
-  int status;
-  struct file_list *flist;
-  char *local_name=NULL;
-  char *dir = NULL;
-  
-  if (verbose > 2)
-    fprintf(FINFO,"server_recv(%d) starting pid=%d\n",argc,(int)getpid());
-
-  if (argc > 0) {
-	  dir = argv[0];
-	  argc--;
-	  argv++;
-	  if (chdir(dir) != 0) {
-		  fprintf(FERROR,"chdir %s : %s (4)\n",
-			  dir,strerror(errno));
-		  exit_cleanup(1);
-	  }    
-  }
+	int status;
+	struct file_list *flist;
+	char *local_name=NULL;
+	char *dir = NULL;
+	extern int delete_mode;
+	extern int am_daemon;
 
-  if (delete_mode)
-    recv_exclude_list(STDIN_FILENO);
+	if (verbose > 2)
+		rprintf(FINFO,"server_recv(%d) starting pid=%d\n",argc,(int)getpid());
+	
+	if (argc > 0) {
+		dir = argv[0];
+		argc--;
+		argv++;
+		if (!am_daemon && chdir(dir) != 0) {
+			rprintf(FERROR,"chdir %s : %s (4)\n",
+				dir,strerror(errno));
+			exit_cleanup(1);
+		}    
+	}
 
-  flist = recv_file_list(STDIN_FILENO);
-  if (!flist || flist->count == 0) {
-    fprintf(FERROR,"nothing to do\n");
-    exit_cleanup(1);
-  }
+	if (delete_mode)
+		recv_exclude_list(f_in);
 
-  if (argc > 0) {    
-	  if (strcmp(dir,".")) {
-		  argv[0] += strlen(dir);
-		  if (argv[0][0] == '/') argv[0]++;
-	  }
-	  local_name = get_local_name(flist,argv[0]);
-  }
+	flist = recv_file_list(f_in);
+	if (!flist || flist->count == 0) {
+		rprintf(FERROR,"nothing to do\n");
+		exit_cleanup(1);
+	}
+	
+	if (argc > 0) {    
+		if (strcmp(dir,".")) {
+			argv[0] += strlen(dir);
+			if (argv[0][0] == '/') argv[0]++;
+		}
+		local_name = get_local_name(flist,argv[0]);
+	}
 
-  status = do_recv(STDIN_FILENO,STDOUT_FILENO,flist,local_name);
-  exit_cleanup(status);
+	status = do_recv(f_in,f_out,flist,local_name);
+	exit_cleanup(status);
 }
 
 
-void start_server(int argc, char *argv[])
+void start_server(int f_in, int f_out, int argc, char *argv[])
 {
-      setup_protocol(STDOUT_FILENO,STDIN_FILENO);
+	extern int cvs_exclude;
+	extern int am_sender;
+
+	setup_protocol(f_out, f_in);
 	
-      if (am_sender) {
-	      recv_exclude_list(STDIN_FILENO);
-	      if (cvs_exclude)
-		      add_cvs_excludes();
-	      do_server_sender(argc,argv);
-      } else {
-	      do_server_recv(argc,argv);
-      }
-      exit_cleanup(0);
+	if (am_sender) {
+		recv_exclude_list(f_in);
+		if (cvs_exclude)
+			add_cvs_excludes();
+		do_server_sender(f_in, f_out, argc, argv);
+	} else {
+		do_server_recv(f_in, f_out, argc, argv);
+	}
+	exit_cleanup(0);
 }
 
-
-static void usage(FILE *f)
+int client_run(int f_in, int f_out, int pid, int argc, char *argv[])
 {
-  fprintf(f,"rsync version %s Copyright Andrew Tridgell and Paul Mackerras\n\n",
-	  VERSION);
-  fprintf(f,"Usage:\t%s [options] src user@host:dest\nOR",RSYNC_NAME);
-  fprintf(f,"\t%s [options] user@host:src dest\n\n",RSYNC_NAME);
-  fprintf(f,"Options:\n");
-  fprintf(f,"-v, --verbose            increase verbosity\n");
-  fprintf(f,"-c, --checksum           always checksum\n");
-  fprintf(f,"-a, --archive            archive mode (same as -rlptDog)\n");
-  fprintf(f,"-r, --recursive          recurse into directories\n");
-  fprintf(f,"-R, --relative           use relative path names\n");
-  fprintf(f,"-b, --backup             make backups (default ~ extension)\n");
-  fprintf(f,"-u, --update             update only (don't overwrite newer files)\n");
-  fprintf(f,"-l, --links              preserve soft links\n");
-  fprintf(f,"-L, --copy-links         treat soft links like regular files\n");
-  fprintf(f,"-H, --hard-links         preserve hard links\n");
-  fprintf(f,"-p, --perms              preserve permissions\n");
-  fprintf(f,"-o, --owner              preserve owner (root only)\n");
-  fprintf(f,"-g, --group              preserve group\n");
-  fprintf(f,"-D, --devices            preserve devices (root only)\n");
-  fprintf(f,"-t, --times              preserve times\n");  
-  fprintf(f,"-S, --sparse             handle sparse files efficiently\n");
-  fprintf(f,"-n, --dry-run            show what would have been transferred\n");
-  fprintf(f,"-W, --whole-file         copy whole files, no incremental checks\n");
-  fprintf(f,"-x, --one-file-system    don't cross filesystem boundaries\n");
-  fprintf(f,"-B, --block-size SIZE    checksum blocking size\n");  
-  fprintf(f,"-e, --rsh COMMAND        specify rsh replacement\n");
-  fprintf(f,"    --rsync-path PATH    specify path to rsync on the remote machine\n");
-  fprintf(f,"-C, --cvs-exclude        auto ignore files in the same way CVS does\n");
-  fprintf(f,"    --delete             delete files that don't exist on the sending side\n");
-  fprintf(f,"    --force              force deletion of directories even if not empty\n");
-  fprintf(f,"    --numeric-ids        don't map uid/gid values by user/group name\n");
-  fprintf(f,"    --timeout TIME       set IO timeout in seconds\n");
-  fprintf(f,"-I, --ignore-times       don't exclude files that match length and time\n");
-  fprintf(f,"-T  --temp-dir DIR       create temporary files in directory DIR\n");
-  fprintf(f,"-z, --compress           compress file data\n");
-  fprintf(f,"    --exclude FILE       exclude file FILE\n");
-  fprintf(f,"    --exclude-from FILE  exclude files listed in FILE\n");
-  fprintf(f,"    --suffix SUFFIX      override backup suffix\n");  
-  fprintf(f,"    --version            print version number\n");  
-
-  fprintf(f,"\n");
-  fprintf(f,"the backup suffix defaults to %s\n",BACKUP_SUFFIX);
-  fprintf(f,"the block size defaults to %d\n",BLOCK_SIZE);  
-}
-
-enum {OPT_VERSION,OPT_SUFFIX,OPT_SENDER,OPT_SERVER,OPT_EXCLUDE,
-      OPT_EXCLUDE_FROM,OPT_DELETE,OPT_NUMERIC_IDS,OPT_RSYNC_PATH,
-      OPT_FORCE,OPT_TIMEOUT};
-
-static char *short_options = "oblLWHpguDCtcahvrRIxnSe:B:T:z";
-
-static struct option long_options[] = {
-  {"version",     0,     0,    OPT_VERSION},
-  {"server",      0,     0,    OPT_SERVER},
-  {"sender",      0,     0,    OPT_SENDER},
-  {"delete",      0,     0,    OPT_DELETE},
-  {"force",       0,     0,    OPT_FORCE},
-  {"numeric-ids", 0,     0,    OPT_NUMERIC_IDS},
-  {"exclude",     1,     0,    OPT_EXCLUDE},
-  {"exclude-from",1,     0,    OPT_EXCLUDE_FROM},
-  {"rsync-path",  1,     0,    OPT_RSYNC_PATH},
-  {"one-file-system",0,  0,    'x'},
-  {"ignore-times",0,     0,    'I'},
-  {"help",        0,     0,    'h'},
-  {"dry-run",     0,     0,    'n'},
-  {"sparse",      0,     0,    'S'},
-  {"cvs-exclude", 0,     0,    'C'},
-  {"archive",     0,     0,    'a'},
-  {"checksum",    0,     0,    'c'},
-  {"backup",      0,     0,    'b'},
-  {"update",      0,     0,    'u'},
-  {"verbose",     0,     0,    'v'},
-  {"recursive",   0,     0,    'r'},
-  {"relative",    0,     0,    'R'},
-  {"devices",     0,     0,    'D'},
-  {"perms",       0,     0,    'p'},
-  {"links",       0,     0,    'l'},
-  {"copy-links",  0,     0,    'L'},
-  {"whole-file",  0,     0,    'W'},
-  {"hard-links",  0,     0,    'H'},
-  {"owner",       0,     0,    'o'},
-  {"group",       0,     0,    'g'},
-  {"times",       0,     0,    't'},
-  {"rsh",         1,     0,    'e'},
-  {"suffix",      1,     0,    OPT_SUFFIX},
-  {"block-size",  1,     0,    'B'},
-  {"timeout",     1,     0,    OPT_TIMEOUT},
-  {"temp-dir",    1,     0,    'T'},
-  {"compress",	  0,	 0,    'z'},
-  {0,0,0,0}};
+	struct file_list *flist;
+	int status = 0, status2 = 0;
+	char *local_name = NULL;
+	extern int am_sender;
 
-RETSIGTYPE sigusr1_handler(int val) {
-	exit_cleanup(1);
+	setup_protocol(f_out,f_in);
+	
+	if (am_sender) {
+		extern int cvs_exclude;
+		extern int delete_mode;
+		if (cvs_exclude)
+			add_cvs_excludes();
+		if (delete_mode) 
+			send_exclude_list(f_out);
+		flist = send_file_list(f_out,argc,argv);
+		if (verbose > 3) 
+			rprintf(FINFO,"file list sent\n");
+		send_files(flist,f_out,f_in);
+		if (pid != -1) {
+			if (verbose > 3)
+				rprintf(FINFO,"waiting on %d\n",pid);
+			waitpid(pid, &status, 0);
+		}
+		report(-1);
+		exit_cleanup(status);
+	}
+	
+	send_exclude_list(f_out);
+	
+	flist = recv_file_list(f_in);
+	if (!flist || flist->count == 0) {
+		rprintf(FINFO,"nothing to do\n");
+		exit_cleanup(0);
+	}
+	
+	local_name = get_local_name(flist,argv[0]);
+	
+	status2 = do_recv(f_in,f_out,flist,local_name);
+	
+	report(f_in);
+	
+	if (pid != -1) {
+		waitpid(pid, &status, 0);
+	}
+	
+	return status | status2;
 }
 
-int main(int argc,char *argv[])
+
+int start_client(int argc, char *argv[])
 {
-    int pid, status = 0, status2 = 0;
-    int opt;
-    int option_index;
-    char *shell_cmd = NULL;
-    char *shell_machine = NULL;
-    char *shell_path = NULL;
-    char *shell_user = NULL;
-    char *p;
-    int f_in,f_out;
-    struct file_list *flist;
-    char *local_name = NULL;
-
-    signal(SIGUSR1, sigusr1_handler);
-
-    starttime = time(NULL);
-    am_root = (getuid() == 0);
-
-    /* we set a 0 umask so that correct file permissions can be
-       carried across */
-    orig_umask = (int)umask(0);
-
-    while ((opt = getopt_long(argc, argv, 
-			      short_options, long_options, &option_index)) 
-	   != -1) {
-      switch (opt) 
-	{
-	case OPT_VERSION:
-	  printf("rsync version %s  protocol version %d\n",
-		 VERSION,PROTOCOL_VERSION);
-	  exit_cleanup(0);
-
-	case OPT_SUFFIX:
-	  backup_suffix = optarg;
-	  break;
-
-	case OPT_RSYNC_PATH:
-	  rsync_path = optarg;
-	  break;
-
-	case 'I':
-	  ignore_times = 1;
-	  break;
-
-	case 'x':
-	  one_file_system=1;
-	  break;
-
-	case OPT_DELETE:
-	  delete_mode = 1;
-	  break;
-
-	case OPT_FORCE:
-	  force_delete = 1;
-	  break;
-
-	case OPT_NUMERIC_IDS:
-	  numeric_ids = 1;
-	  break;
-
-	case OPT_EXCLUDE:
-	  add_exclude(optarg);
-	  break;
-
-	case OPT_EXCLUDE_FROM:
-	  add_exclude_file(optarg,1);
-	  break;
-
-	case 'h':
-	  usage(FINFO);
-	  exit_cleanup(0);
-
-	case 'b':
-	  make_backups=1;
-	  break;
-
-	case 'n':
-	  dry_run=1;
-	  break;
-
-	case 'S':
-	  sparse_files=1;
-	  break;
-
-	case 'C':
-	  cvs_exclude=1;
-	  break;
-
-	case 'u':
-	  update_only=1;
-	  break;
-
-	case 'l':
-	  preserve_links=1;
-	  break;
-
-	case 'L':
-	  copy_links=1;
-	  break;
-
-	case 'W':
-	  whole_file=1;
-	  break;
-
-	case 'H':
-#if SUPPORT_HARD_LINKS
-	  preserve_hard_links=1;
-#else 
-	  fprintf(FERROR,"ERROR: hard links not supported on this platform\n");
-	  exit_cleanup(1);
-#endif
-	  break;
+	char *p;
+	char *shell_machine = NULL;
+	char *shell_path = NULL;
+	char *shell_user = NULL;
+	int pid;
+	int f_in,f_out;
+	extern int local_server;
+	extern int am_sender;
+	extern char *shell_cmd;
+
+	p = strchr(argv[0],':');
+
+	if (p) {
+		if (p[1] == ':') {
+			*p = 0;
+			return start_socket_client(argv[0], p+2, argc-1, argv+1);
+		}
 
-	case 'p':
-	  preserve_perms=1;
-	  break;
-
-	case 'o':
-	  preserve_uid=1;
-	  break;
-
-	case 'g':
-	  preserve_gid=1;
-	  break;
-
-	case 'D':
-	  preserve_devices=1;
-	  break;
-
-	case 't':
-	  preserve_times=1;
-	  break;
-
-	case 'c':
-	  always_checksum=1;
-	  break;
-
-	case 'v':
-	  verbose++;
-	  break;
-
-	case 'a':
-	  recurse=1;
-#if SUPPORT_LINKS
-	  preserve_links=1;
-#endif
-	  preserve_perms=1;
-	  preserve_times=1;
-	  preserve_gid=1;
-	  if (am_root) {
-	    preserve_devices=1;
-	    preserve_uid=1;
-	  }
-	  break;
-
-	case OPT_SERVER:
-	  am_server = 1;
-	  break;
-
-	case OPT_SENDER:
-	  if (!am_server) {
-	    usage(FERROR);
-	    exit_cleanup(1);
-	  }
-	  am_sender = 1;
-	  break;
-
-	case 'r':
-	  recurse = 1;
-	  break;
-
-	case 'R':
-	  relative_paths = 1;
-	  break;
-
-	case 'e':
-	  shell_cmd = optarg;
-	  break;
-
-	case 'B':
-	  block_size = atoi(optarg);
-	  break;
-
-	case OPT_TIMEOUT:
-	  io_timeout = atoi(optarg);
-	  break;
-
-	case 'T':
-		tmpdir = optarg;
-		break;
-
-        case 'z':
-	  do_compression = 1;
-	  break;
-
-	default:
-	  /* fprintf(FERROR,"bad option -%c\n",opt); */
-	  exit_cleanup(1);
-	}
-    }
+		if (argc < 2) {
+			usage(FERROR);
+			exit_cleanup(1);
+		}
 
-    while (optind--) {
-      argc--;
-      argv++;
-    }
+		am_sender = 0;
+		*p = 0;
+		shell_machine = argv[0];
+		shell_path = p+1;
+		argc--;
+		argv++;
+	} else {
+		am_sender = 1;
 
-    signal(SIGCHLD,SIG_IGN);
-    signal(SIGINT,SIGNAL_CAST sig_int);
-    signal(SIGPIPE,SIGNAL_CAST sig_int);
-    signal(SIGHUP,SIGNAL_CAST sig_int);
+		p = strchr(argv[argc-1],':');
+		if (!p) {
+			local_server = 1;
+		} else if (p[1] == ':') {
+			*p = 0;
+			return start_socket_client(argv[argc-1], p+2, argc-1, argv);
+		}
 
-    if (dry_run)
-      verbose = MAX(verbose,1);
+		if (argc < 2) {
+			usage(FERROR);
+			exit_cleanup(1);
+		}
+		
+		if (local_server) {
+			shell_machine = NULL;
+			shell_path = argv[argc-1];
+		} else {
+			*p = 0;
+			shell_machine = argv[argc-1];
+			shell_path = p+1;
+		}
+		argc--;
+	}
+	
+	if (shell_machine) {
+		p = strchr(shell_machine,'@');
+		if (p) {
+			*p = 0;
+			shell_user = shell_machine;
+			shell_machine = p+1;
+		}
+	}
 
-#ifndef SUPPORT_LINKS
-    if (!am_server && preserve_links) {
-	    fprintf(FERROR,"ERROR: symbolic links not supported\n");
-	    exit_cleanup(1);
-    }
+	if (verbose > 3) {
+		rprintf(FINFO,"cmd=%s machine=%s user=%s path=%s\n",
+			shell_cmd?shell_cmd:"",
+			shell_machine?shell_machine:"",
+			shell_user?shell_user:"",
+			shell_path?shell_path:"");
+	}
+	
+	if (!am_sender && argc != 1) {
+		usage(FERROR);
+		exit_cleanup(1);
+	}
+	
+	pid = do_cmd(shell_cmd,shell_machine,shell_user,shell_path,&f_in,&f_out);
+	
+#if HAVE_SETLINEBUF
+	setlinebuf(stdout);
+	setlinebuf(stderr);
 #endif
 
-    if (am_server) {
-	    start_server(argc, argv);
-    }
-
-    if (argc < 2) {
-      usage(FERROR);
-      exit_cleanup(1);
-    }
-
-    p = strchr(argv[0],':');
+	return client_run(f_in, f_out, pid, argc, argv);
+}
 
-    if (p) {
-      am_sender = 0;
-      *p = 0;
-      shell_machine = argv[0];
-      shell_path = p+1;
-      argc--;
-      argv++;
-    } else {
-      am_sender = 1;
-
-      p = strchr(argv[argc-1],':');
-      if (!p) {
-	local_server = 1;
-      }
 
-      if (local_server) {
-	shell_machine = NULL;
-	shell_path = argv[argc-1];
-      } else {
-	*p = 0;
-	shell_machine = argv[argc-1];
-	shell_path = p+1;
-      }
-      argc--;
-    }
+RETSIGTYPE sigusr1_handler(int val) {
+	exit_cleanup(1);
+}
 
-    if (shell_machine) {
-      p = strchr(shell_machine,'@');
-      if (p) {
-	*p = 0;
-	shell_user = shell_machine;
-	shell_machine = p+1;
-      }
-    }
+int main(int argc,char *argv[])
+{       
+	extern int am_root;
+	extern int orig_umask;
+	extern int dry_run;
+	extern int am_daemon;
+	extern int am_server;
+
+	signal(SIGUSR1, sigusr1_handler);
+
+	starttime = time(NULL);
+	am_root = (getuid() == 0);
+
+	if (argc < 2) {
+		usage(FERROR);
+		exit(1);
+	}
 
-    if (verbose > 3) {
-      fprintf(FINFO,"cmd=%s machine=%s user=%s path=%s\n",
-	      shell_cmd?shell_cmd:"",
-	      shell_machine?shell_machine:"",
-	      shell_user?shell_user:"",
-	      shell_path?shell_path:"");
-    }
-    
-    if (!am_sender && argc != 1) {
-      usage(FERROR);
-      exit_cleanup(1);
-    }
+	/* we set a 0 umask so that correct file permissions can be
+	   carried across */
+	orig_umask = (int)umask(0);
+
+	parse_arguments(argc, argv);
+
+	argc -= optind;
+	argv += optind;
+	optind = 0;
+
+	signal(SIGCHLD,SIG_IGN);
+	signal(SIGINT,SIGNAL_CAST sig_int);
+	signal(SIGPIPE,SIGNAL_CAST sig_int);
+	signal(SIGHUP,SIGNAL_CAST sig_int);
 
-    pid = do_cmd(shell_cmd,shell_machine,shell_user,shell_path,&f_in,&f_out);
+	if (am_daemon) {
+		return daemon_main();
+	}
 
-    setup_protocol(f_out,f_in);
+	if (dry_run)
+		verbose = MAX(verbose,1);
 
-#if HAVE_SETLINEBUF
-    setlinebuf(FINFO);
-    setlinebuf(FERROR);
+#ifndef SUPPORT_LINKS
+	if (!am_server && preserve_links) {
+		rprintf(FERROR,"ERROR: symbolic links not supported\n");
+		exit_cleanup(1);
+	}
 #endif
 
-    if (verbose > 3) 
-      fprintf(FINFO,"parent=%d child=%d sender=%d recurse=%d\n",
-	      (int)getpid(),pid,am_sender,recurse);
-
-    if (am_sender) {
-      if (cvs_exclude)
-	add_cvs_excludes();
-      if (delete_mode) 
-	send_exclude_list(f_out);
-      flist = send_file_list(f_out,argc,argv);
-      if (verbose > 3) 
-	fprintf(FINFO,"file list sent\n");
-      send_files(flist,f_out,f_in);
-      if (verbose > 3)
-	fprintf(FINFO,"waiting on %d\n",pid);
-      waitpid(pid, &status, 0);
-      report(-1);
-      exit_cleanup(status);
-    }
-
-    send_exclude_list(f_out);
-
-    flist = recv_file_list(f_in);
-    if (!flist || flist->count == 0) {
-      fprintf(FINFO,"nothing to do\n");
-      exit_cleanup(0);
-    }
-
-    local_name = get_local_name(flist,argv[0]);
-
-    status2 = do_recv(f_in,f_out,flist,local_name);
-
-    report(f_in);
-
-    waitpid(pid, &status, 0);
+	if (am_server) {
+		start_server(STDIN_FILENO, STDOUT_FILENO, argc, argv);
+	}
 
-    return status | status2;
+	return start_client(argc, argv);
 }
 
