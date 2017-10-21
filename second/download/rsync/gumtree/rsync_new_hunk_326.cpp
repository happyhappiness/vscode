  }

  args[argc++] = rsync_path;

  server_options(args,&argc);

  args[argc++] = ".";

  if (path && *path) 
	  args[argc++] = path;

  args[argc] = NULL;

  if (verbose > 3) {
    fprintf(FINFO,"cmd=");
    for (i=0;i<argc;i++)
      fprintf(FINFO,"%s ",args[i]);
    fprintf(FINFO,"\n");
  }

  ret = piped_child(args,f_in,f_out);
  if (dir) free(dir);

  return ret;
