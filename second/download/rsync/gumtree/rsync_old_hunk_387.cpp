	  if (!flist->files)
		  out_of_memory("send_file_name");
  }

  if (strcmp(file->basename,"")) {
    flist->files[flist->count++] = file;
    send_file_entry(file,f);
  }

  if (S_ISDIR(file->mode) && recursive) {
    char **last_exclude_list = local_exclude_list;
    send_directory(f,flist,f_name(file));
    local_exclude_list = last_exclude_list;
