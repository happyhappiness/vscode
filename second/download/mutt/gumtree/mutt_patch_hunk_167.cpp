 	printf (_("Debugging at level %d.\n"), debuglevel);
 #else
 	printf _("DEBUG was not defined during compilation.  Ignored.\n");
 #endif
 	break;
 
+      case 'E':
+        edit_infile = 1;
+        break;
+
       case 'e':
 	commands = mutt_add_list (commands, optarg);
 	break;
 
       case 'H':
 	draftFile = optarg;
