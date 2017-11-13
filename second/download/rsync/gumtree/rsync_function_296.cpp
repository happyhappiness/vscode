static int delete_already_done(struct file_list *flist,int j)
{
	int low=0,high=j-1;
	char *name;
	char *p;

	if (j == 0) return 0;

	name = strdup(flist->files[j].name);

	if (!name) {
		fprintf(FERROR,"out of memory in delete_already_done");
		exit_cleanup(1);
	}

	p = strrchr(name,'/');
	if (!p) {
		free(name);
		return 0;
	}
	*p = 0;

	while (low != high) {
		int mid = (low+high)/2;
		int ret = strcmp(flist->files[flist_up(flist, mid)].name,name);
		if (ret == 0) {
			free(name);
			return 1;
		}
		if (ret > 0) {
			high=mid;
		} else {
			low=mid+1;
		}
	}

	low = flist_up(flist, low);

	if (strcmp(flist->files[low].name,name) == 0) {
		free(name);
		return 1;
	}

	free(name);
	return 0;
}