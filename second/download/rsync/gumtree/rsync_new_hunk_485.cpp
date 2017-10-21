{
	int i,l;
	STRUCT_STAT st;
	char *p,*dir;
	char lastpath[MAXPATHLEN]="";
	struct file_list *flist;
	int64 start_write;

	if (verbose && recurse && !am_server && f != -1) {
		rprintf(FINFO,"building file list ... ");
		rflush(FINFO);
	}

	start_write = stats.total_written;

	flist = (struct file_list *)malloc(sizeof(flist[0]));
	if (!flist) out_of_memory("send_file_list");

	flist->count=0;
	flist->malloced = 1000;
	flist->files = (struct file_struct **)malloc(sizeof(flist->files[0])*
