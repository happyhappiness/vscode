  struct file_list *local_file_list;
  int i, j;

  if (cvs_exclude)
    add_cvs_excludes();

  for (j=0;j<flist->count;j++) {
	  char *name = flist->files[j].name;

	  if (!S_ISDIR(flist->files[j].mode)) continue;

	  if (delete_already_done(flist, j)) continue;

	  if (!(local_file_list = send_file_list(-1,1,&name)))
		  continue;

	  if (verbose > 1)
		  fprintf(FINFO,"deleting in %s\n", name);

	  for (i=local_file_list->count-1;i>=0;i--) {
		  if (!local_file_list->files[i].name) continue;
		  if (-1 == flist_find(flist,&local_file_list->files[i])) {
			  delete_one(&local_file_list->files[i]);
		  }    
	  }
  }
}

static char *cleanup_fname = NULL;

void exit_cleanup(int code)
{
	if (cleanup_fname)
		unlink(cleanup_fname);
	signal(SIGUSR1, SIG_IGN);
	if (code) {
#ifdef GETPGRP_VOID
		kill(-getpgrp(), SIGUSR1);
#else
		kill(-getpgrp(getpid()), SIGUSR1);
#endif
	}
	exit(code);
}

void sig_int(void)
{
