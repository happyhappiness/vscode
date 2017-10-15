 	{
 	  fprintf (stderr, _("Error: value '%s' is invalid for -d.\n"), optarg);
 	  return 1;
 	}
 	printf (_("Debugging at level %d.\n"), debuglevel);
 #else
-	printf _("DEBUG was not defined during compilation.  Ignored.\n");
+	printf ("%s", _("DEBUG was not defined during compilation.  Ignored.\n"));
 #endif
 	break;
 
       case 'E':
         edit_infile = 1;
         break;
