static int delete_already_done(struct file_list *flist,int j)
{
	int i;
	STRUCT_STAT st;

	if (link_stat(f_name(flist->files[j]), &st)) return 1;

	for (i=0;i<dlist_len;i++) {
		if (st.st_ino == delete_list[i].inode &&
		    st.st_dev == delete_list[i].dev)
			return 1;
	}

	return 0;
}