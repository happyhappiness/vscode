 
 	case OPT_EXCLUDE_FROM:
 	  add_exclude_file(optarg,1);
 	  break;
 
 	case 'h':
-	  usage(stdout);
+	  usage(FINFO);
 	  exit_cleanup(0);
 
 	case 'b':
 	  make_backups=1;
 	  break;
 
 	case 'n':
 	  dry_run=1;
 	  break;
 
+	case 'S':
+	  sparse_files=1;
+	  break;
+
 	case 'C':
 	  cvs_exclude=1;
 	  break;
 
 	case 'u':
 	  update_only=1;
 	  break;
 
-#if SUPPORT_LINKS
 	case 'l':
+#if SUPPORT_LINKS
 	  preserve_links=1;
+#endif
 	  break;
+
+	case 'H':
+#if SUPPORT_HARD_LINKS
+	  preserve_hard_links=1;
 #endif
+	  break;
 
 	case 'p':
 	  preserve_perms=1;
 	  break;
 
 	case 'o':
 	  if (getuid() == 0) {
 	    preserve_uid=1;
 	  } else {
-	    fprintf(stderr,"-o only allowed for root\n");
+	    fprintf(FERROR,"-o only allowed for root\n");
 	    exit_cleanup(1);
 	  }
 	  break;
 
 	case 'g':
 	  preserve_gid=1;
 	  break;
 
 	case 'D':
 	  if (getuid() == 0) {
 	    preserve_devices=1;
 	  } else {
-	    fprintf(stderr,"-D only allowed for root\n");
+	    fprintf(FERROR,"-D only allowed for root\n");
 	    exit_cleanup(1);
 	  }
 	  break;
 
 	case 't':
 	  preserve_times=1;
