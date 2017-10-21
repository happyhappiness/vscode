    
	if (!(hlink_list = 
	      (struct file_struct *)malloc(sizeof(hlink_list[0])*flist->count)))
		out_of_memory("init_hard_links");

	for (i = 0; i < flist->count; i++)
		memcpy(&hlink_list[i], flist->files[i], sizeof(hlink_list[0]));

	qsort(hlink_list,flist->count,
	      sizeof(hlink_list[0]),
	      (int (*)())hlink_compare);

	hlink_count=flist->count;
