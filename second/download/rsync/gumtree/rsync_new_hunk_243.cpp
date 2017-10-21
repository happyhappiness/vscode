
  file = make_file(fname);

  if (!file) return;  
  
  if (flist->count >= flist->malloced) {
	  if (flist->malloced < 100)
		  flist->malloced += 100;
	  else
		  flist->malloced *= 1.8;
	  flist->files = (struct file_struct *)realloc(flist->files,
						       sizeof(flist->files[0])*
						       flist->malloced);
	  if (!flist->files)
		  out_of_memory("send_file_name");
  }

  if (strcmp(file->name,"/")) {
    flist->files[flist->count++] = *file;    
    send_file_entry(file,f);
  }

  if (S_ISDIR(file->mode) && recurse) {
    char **last_exclude_list = local_exclude_list;
