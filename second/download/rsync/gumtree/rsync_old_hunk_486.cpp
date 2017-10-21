	  io_error |= read_int(f);
  }

  if (verbose > 2)
    rprintf(FINFO,"recv_file_list done\n");

  return flist;

oom:
    out_of_memory("recv_file_list");
    return NULL; /* not reached */
}
