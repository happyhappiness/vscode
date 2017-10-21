  if (hlink_list) free(hlink_list);
    
  if (!(hlink_list = 
	(struct file_struct *)malloc(sizeof(hlink_list[0])*flist->count)))
    out_of_memory("init_hard_links");

  bcopy((char *)flist->files,hlink_list,sizeof(hlink_list[0])*flist->count);

  qsort(hlink_list,flist->count,
	sizeof(hlink_list[0]),
	(int (*)())hlink_compare);

  hlink_count=flist->count;
