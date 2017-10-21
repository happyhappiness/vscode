	flist->files = (struct file_struct **)malloc(sizeof(flist->files[0])*
						     flist->malloced);
	if (!flist->files) out_of_memory("send_file_list");
#if ARENA_SIZE > 0
	flist->string_area = string_area_new(0);
#else
	flist->string_area = NULL;
#endif
	return flist;
}
/*
 * free up all elements in a flist
 */
