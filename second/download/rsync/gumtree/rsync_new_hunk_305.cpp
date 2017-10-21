    /* now pretend the file didn't exist */
    write_int(f_out,i);
    if (!dry_run) send_sums(NULL,f_out);    
    return;
  }

  if (update_only && st.st_mtime > file->modtime) {
    if (verbose > 1)
      fprintf(FERROR,"%s is newer\n",fname);
    return;
  }

  if (skip_file(fname, file, &st)) {
    set_perms(fname,file,&st,1);
    return;
  }

  if (dry_run) {
    write_int(f_out,i);
