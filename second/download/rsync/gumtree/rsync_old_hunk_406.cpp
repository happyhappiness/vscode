  /* if protocol version is >= 17 then recv the io_error flag */
  if (f != -1 && remote_version >= 17) {
	  io_error |= read_int(f);
  }

  if (verbose > 2)
    fprintf(FINFO,"recv_file_list done\n");

  return flist;

oom:
    out_of_memory("recv_file_list");
    return NULL; /* not reached */
