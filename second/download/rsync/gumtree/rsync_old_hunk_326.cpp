  }

  args[argc++] = rsync_path;

  server_options(args,&argc);

  if (path && *path) {
    dir = strdup(path);
    p = strrchr(dir,'/');
    if (p && !relative_paths) {
      *p = 0;
      if (!dir[0])
	args[argc++] = "/";
      else
	args[argc++] = dir;
      p++;
    } else {
      args[argc++] = ".";
      p = dir;
    }
    if (p[0])
      args[argc++] = path;
  }

  args[argc] = NULL;

  if (verbose > 3) {
    fprintf(FERROR,"cmd=");
    for (i=0;i<argc;i++)
      fprintf(FERROR,"%s ",args[i]);
    fprintf(FERROR,"\n");
  }

  ret = piped_child(args,f_in,f_out);
  if (dir) free(dir);

  return ret;
