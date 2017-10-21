  struct file_list *local_file_list;
  int i, j;

  if (cvs_exclude)
    add_cvs_excludes();

  if (io_error) {
	  fprintf(FINFO,"IO error encountered - skipping file deletion\n");
	  return;
  }

  for (j=0;j<flist->count;j++) {
	  char *name = f_name(flist->files[j]);

	  if (!S_ISDIR(flist->files[j]->mode)) continue;

	  if (delete_already_done(flist, j)) continue;

	  if (!(local_file_list = send_file_list(-1,1,&name)))
		  continue;

	  if (verbose > 1)
		  fprintf(FINFO,"deleting in %s\n", name);

	  for (i=local_file_list->count-1;i>=0;i--) {
		  if (!local_file_list->files[i]->basename) continue;
		  if (-1 == flist_find(flist,local_file_list->files[i])) {
			  delete_one(local_file_list->files[i]);
		  }    
	  }
	  flist_free(local_file_list);
  }
}

static char *cleanup_fname;

void exit_cleanup(int code)
{
	if (cleanup_fname)
		do_unlink(cleanup_fname);
	signal(SIGUSR1, SIG_IGN);
	if (code) {
		kill_all(SIGUSR1);
	}
	exit(code);
}

void sig_int(void)
{
