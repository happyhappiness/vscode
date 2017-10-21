  }


  if (verbose > 2)
    fprintf(stderr,"received %d names\n",flist->count);

  return flist;

oom:
    out_of_memory("recv_file_list");
    return NULL; /* not reached */
}

