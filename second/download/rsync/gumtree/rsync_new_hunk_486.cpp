	  io_error |= read_int(f);
  }

  if (verbose > 2)
    rprintf(FINFO,"recv_file_list done\n");

  stats.flist_size = stats.total_read - start_read;
  stats.num_files = flist->count;

  return flist;

oom:
    out_of_memory("recv_file_list");
    return NULL; /* not reached */
}
