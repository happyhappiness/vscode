void send_file_name(int f,struct file_list *flist,char *fname,
			   int recursive, unsigned base_flags)
{
  struct file_struct *file;

  file = make_file(f,fname, &flist->string_area, 0);

  if (!file) return;  
  
  if (flist->count >= flist->malloced) {
	  if (flist->malloced < 1000)
		  flist->malloced += 1000;
	  else
		  flist->malloced *= 2;
	  flist->files = (struct file_struct **)realloc(flist->files,
							sizeof(flist->files[0])*
							flist->malloced);
	  if (!flist->files)
		  out_of_memory("send_file_name");
  }

  if (write_batch) /*  dw  */
    file->flags = FLAG_DELETE;

  if (strcmp(file->basename,"")) {
    flist->files[flist->count++] = file;
    send_file_entry(file,f,base_flags);
  }

  if (S_ISDIR(file->mode) && recursive) {
	  struct exclude_struct **last_exclude_list = local_exclude_list;
	  send_directory(f,flist,f_name(file));
	  local_exclude_list = last_exclude_list;
	  return;
  }
}