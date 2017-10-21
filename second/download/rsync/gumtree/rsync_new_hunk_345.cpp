	fprintf(FERROR,"recv_generator failed to open %s\n",fname);
    }
    return;
  }

  if (!S_ISREG(st.st_mode)) {
    if (delete_file(fname) != 0) {
      return;
    }

    /* now pretend the file didn't exist */
    write_int(f_out,i);
    if (!dry_run) send_sums(NULL,f_out);    
    return;
  }

  if (update_only && st.st_mtime > file->modtime) {
    if (verbose > 1)
      fprintf(FINFO,"%s is newer\n",fname);
    return;
  }

  if (skip_file(fname, file, &st)) {
    set_perms(fname,file,&st,1);
    return;
