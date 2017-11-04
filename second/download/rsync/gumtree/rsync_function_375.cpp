static int delete_already_done(struct file_list *flist,int j)
{
	int low=0,high=j-1;
	char *name;
	char *p;

	if (j == 0) return 0;

	name = strdup(f_name(flist->files[j]));

	if (!name) {
		fprintf(FERROR,"out of memory in delete_already_done");
		exit_cleanup(1);
	}

	name[strlen(name)-2] = 0;

	p = strrchr(name,'/');
	if (!p) {
		free(name);
		return 0;
	}
	*p = 0;

	strcat(name,"/.");

	while (low != high) {
		int mid = (low+high)/2;
		int ret = strcmp(f_name(flist->files[flist_up(flist, mid)]),name);
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

	if (strcmp(f_name(flist->files[low]),name) == 0) {
		free(name);
		return 1;
	}

	free(name);
	return 0;
}