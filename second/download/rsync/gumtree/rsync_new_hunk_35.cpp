  }

  if (always_checksum && S_ISREG(st.st_mode)) {
    file_checksum(fname,sum,st.st_size);
  }

  if (st.st_size == flist->files[i].length &&
      (st.st_mtime == flist->files[i].modtime ||
       (always_checksum && S_ISREG(st.st_mode) && 	  
	memcmp(sum,flist->files[i].sum,SUM_LENGTH) == 0))) {
    set_perms(fname,&flist->files[i],&st,1);
    return;
  }

  if (dry_run) {
    write_int(f_out,i);
    return;
