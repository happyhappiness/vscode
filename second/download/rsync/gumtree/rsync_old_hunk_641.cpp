{
	unsigned char flags;

	fdb_open = 1;
	fdb_close = 0;

	batch_flist = (struct file_list *) malloc(sizeof(batch_flist[0]));
	if (!batch_flist) {
		out_of_memory("create_flist_from_batch");
	}
	batch_flist->count = 0;
	batch_flist->malloced = 1000;
	batch_flist->files =
	    (struct file_struct **) malloc(sizeof(batch_flist->files[0]) *
					   batch_flist->malloced);
	if (!batch_flist->files) {
		out_of_memory("create_flist_from_batch");
	}

	for (flags = read_batch_flags(); flags; flags = read_batch_flags()) {

