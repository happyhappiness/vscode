{
      fprintf ( stderr, 
                "%s: supplied filename is suspiciously (>= %d chars) long.  Bye!\n",
                progName, (int)strlen(argv[1]) );
      exit(1);
   }