static int hlink_count;
#endif

void init_hard_links(struct file_list *flist)
{
#if SUPPORT_HARD_LINKS
	int i;
	if (flist->count < 2) return;

	if (hlink_list) free(hlink_list);
    
	if (!(hlink_list = 
	      (struct file_struct *)malloc(sizeof(hlink_list[0])*flist->count)))
		out_of_memory("init_hard_links");

	for (i = 0; i < flist->count; i++)
		bcopy(flist->files[i], &hlink_list[i], sizeof(hlink_list[0]));

	qsort(hlink_list,flist->count,
	      sizeof(hlink_list[0]),
	      (int (*)())hlink_compare);

	hlink_count=flist->count;
#endif
}

/* check if a file should be skipped because it is the same as an
   earlier hard link */
int check_hard_link(struct file_struct *file)
