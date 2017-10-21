
  return total;
}



void generate_files(int f,struct file_list *flist,char *local_name)
{
  int i;

  if (verbose > 2)
    fprintf(stderr,"generator starting pid=%d count=%d\n",
	    (int)getpid(),flist->count);

  for (i = 0; i < flist->count; i++) {
    if (S_ISDIR(flist->files[i].mode)) {
      if (dry_run) continue;
      if (mkdir(flist->files[i].name,flist->files[i].mode) != 0 &&
	  errno != EEXIST) {
	fprintf(stderr,"mkdir %s : %s\n",
		flist->files[i].name,strerror(errno));
      }
      continue;
    }
    recv_generator(local_name?local_name:flist->files[i].name,
		   flist,i,f);
  }
  write_int(f,-1);
  write_flush(f);
  if (verbose > 1)
    fprintf(stderr,"generator wrote %d\n",write_total());
}
