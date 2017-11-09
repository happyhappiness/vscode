int
cmd_main (int argc, const char *argv[])
{
  /* Default values for command line options.  */
  /* unsigned short int show_variables = 0; */

  switch (argc)
	{
	case 1:
	  error ("we won't substitute all variables on stdin for you");
	  break;
	  /*
	  all_variables = 1;
      subst_from_stdin ();
	  */
	case 2:
	  /* echo '$foo and $bar' | git sh-i18n--envsubst --variables '$foo and $bar' */
	  all_variables = 0;
	  note_variables (argv[1]);
      subst_from_stdin ();
	  break;
	case 3:
	  /* git sh-i18n--envsubst --variables '$foo and $bar' */
	  if (strcmp(argv[1], "--variables"))
		error ("first argument must be --variables when two are given");
	  /* show_variables = 1; */
      print_variables (argv[2]);
	  break;
	default:
	  error ("too many arguments");
	  break;
	}

  /* Close standard error.  This is simpler than fwriteerror_no_ebadf, because
     upon failure we don't need an errno - all we can do at this point is to
     set an exit status.  */
  errno = 0;
  if (ferror (stderr) || fflush (stderr))
    {
      fclose (stderr);
      exit (EXIT_FAILURE);
    }
  if (fclose (stderr) && errno != EBADF)
    exit (EXIT_FAILURE);

  exit (EXIT_SUCCESS);
}