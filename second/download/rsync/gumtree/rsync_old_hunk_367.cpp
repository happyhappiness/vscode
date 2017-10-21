static int hlink_count;
#endif

void init_hard_links(struct file_list *flist)
{
#if SUPPORT_HARD_LINKS
  if (flist->count < 2) return;

  if (hlink_list) free(hlink_list);
    
  if (!(hlink_list = 
	(struct file_struct *)malloc(sizeof(hlink_list[0])*flist->count)))
    out_of_memory("init_hard_links");

  bcopy((char *)flist->files,
	(char *)hlink_list,
	sizeof(hlink_list[0])*flist->count);

  qsort(hlink_list,flist->count,
	sizeof(hlink_list[0]),
	(int (*)())hlink_compare);

  hlink_count=flist->count;
#endif
}

/* check if a file should be skipped because it is the same as an
   earlier hard link */
int check_hard_link(struct file_struct *file)
