	}

	return (st->st_mtime == file->modtime);
}


/* use a larger block size for really big files */
int adapt_block_size(struct file_struct *file, int bsize)
{
	int ret = file->length / (10000); /* rough heuristic */
	ret = ret & ~15; /* multiple of 16 */
	if (ret < bsize) ret = bsize;
	if (ret > CHUNK_SIZE/2) ret = CHUNK_SIZE/2;
	return ret;
}

void recv_generator(char *fname,struct file_list *flist,int i,int f_out)
{  
  int fd;
  struct stat st;
  struct map_struct *buf;
  struct sum_struct *s;
  int statret;
  struct file_struct *file = flist->files[i];

  if (verbose > 2)
    fprintf(FINFO,"recv_generator(%s,%d)\n",fname,i);

  statret = link_stat(fname,&st);

  if (S_ISDIR(file->mode)) {
    if (dry_run) return;
    if (statret == 0 && !S_ISDIR(st.st_mode)) {
      if (do_unlink(fname) != 0) {
	fprintf(FERROR,"unlink %s : %s\n",fname,strerror(errno));
	return;
      }
      statret = -1;
    }
    if (statret != 0 && mkdir(fname,file->mode) != 0 && errno != EEXIST) {
