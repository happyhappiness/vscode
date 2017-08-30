  char *filename;

  char buf[TAR_MAXPATHLEN];

  int i;

  char *pathname = 0;



  while ((i = th_read(t)) == 0)

  {

    pathname = th_get_pathname(t);

    filename = pathname;



    if (fnmatch(globname, filename, FNM_PATHNAME | FNM_PERIOD))

    {

      if (pathname)

        {

        free(pathname);

        pathname = 0;

        }



      if (TH_ISREG(t) && tar_skip_regfile(t))

        return -1;

      continue;

    }



    if (t->options & TAR_VERBOSE)

      th_print_long_ls(t);



    if (prefix != NULL)

      snprintf(buf, sizeof(buf), "%s/%s", prefix, filename);

    else

      strlcpy(buf, filename, sizeof(buf));



    if (tar_extract_file(t, filename) != 0)

      {

      if (pathname)

        {

        free(pathname);

        pathname = 0;

        }

      return -1;

      }



    if (pathname)

      {

      free(pathname);

      pathname = 0;

      }

  }



  return (i == 1 ? 0 : -1);

