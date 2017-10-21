      fprintf(FERROR,"deleting directory %s\n",f->name);      
    }
  }
}


/* yuck! This function wouldn't have been necessary if I had the sorting
   algorithm right. Unfortunately fixing the sorting algorithm would introduce
   a backward incompatibility as file list indexes are sent over the link.

   The aim is to see if a directory has already had the deletion algorithm applied
   to it (due to recursion), and if so to skip it. The bisection is to 
   prevent this being an n^2 algorithm */
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


/* this deletes any files on the receiving side that are not present
   on the sending side. For version 1.6.4 I have changed the behaviour
   to match more closely what most people seem to expect of this option */
static void delete_files(struct file_list *flist)
{
  struct file_list *local_file_list;
  int i, j;

  if (cvs_exclude)
    add_cvs_excludes();

  for (j=0;j<flist->count;j++) {
	  char *name = flist->files[j].name;

	  if (!S_ISDIR(flist->files[j].mode)) continue;

	  if (delete_already_done(flist, j)) continue;

	  if (!(local_file_list = send_file_list(-1,1,&name)))
		  continue;

	  if (verbose > 1)
		  fprintf(FINFO,"deleting in %s\n", name);

	  for (i=local_file_list->count-1;i>=0;i--) {
		  if (!local_file_list->files[i].name) continue;
		  if (-1 == flist_find(flist,&local_file_list->files[i])) {
			  delete_one(&local_file_list->files[i]);
		  }    
