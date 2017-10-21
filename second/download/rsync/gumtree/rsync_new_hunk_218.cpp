	fprintf(FERROR,"recv_generator failed to open %s\n",fname);
    }
    return;
  }

  if (!S_ISREG(st.st_mode)) {
    /* its not a regular file on the receiving end, but it is on the
       sending end. If its a directory then skip it (too dangerous to
       do a recursive deletion??) otherwise try to unlink it */
    if (S_ISDIR(st.st_mode)) {
      fprintf(FERROR,"ERROR: %s is a directory\n",fname);
      return;
    }
    if (unlink(fname) != 0) {
      fprintf(FERROR,"%s : not a regular file (generator)\n",fname);
      return;
    }

    /* now pretend the file didn't exist */
    write_int(f_out,i);
    if (!dry_run) send_sums(NULL,f_out);    
    return;
  }

  if (update_only && st.st_mtime >= file->modtime) {
    if (verbose > 1)
      fprintf(FERROR,"%s is newer\n",fname);
