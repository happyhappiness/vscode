    if (S_ISREG(flist->files[i].mode))
      total_size += flist->files[i].length;

    flist->count++;

    if (verbose > 2)
      fprintf(stderr,"recv_file_name(%s)\n",flist->files[i].name);
  }


  if (verbose > 2)
    fprintf(stderr,"received %d names\n",flist->count);

  clean_flist(flist);

  return flist;

oom:
    out_of_memory("recv_file_list");
    return NULL; /* not reached */
}


static int flist_compare(struct file_struct *f1,struct file_struct *f2)
{
  if (!f1->name && !f2->name) return 0;
  if (!f1->name) return -1;
  if (!f2->name) return 1;
  return strcmp(f1->name,f2->name);
}
