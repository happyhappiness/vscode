{
      fprintf (
         stderr,
         "bzip2: file name\n`%s'\n"
         "is suspiciously (more than %d chars) long.\n"
         "Try using a reasonable file name instead.  Sorry! :-)\n",
         from, FILE_NAME_LEN-10
      );
      setExit(1);
      exit(exitValue);
   }