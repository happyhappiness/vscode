
  if (dry_run) {
    write_int(f_out,i);
    return;
  }

  if (whole_file) {
    write_int(f_out,i);
    send_sums(NULL,f_out);    
    return;
  }

  /* open the file */  
  fd = open(fname,O_RDONLY);

  if (fd == -1) {
    fprintf(FERROR,"failed to open %s : %s\n",fname,strerror(errno));
    return;
