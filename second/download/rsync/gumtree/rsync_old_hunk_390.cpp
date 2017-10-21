      fprintf(FINFO,"deleting directory %s\n",f_name(f));      
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


/* this deletes any files on the receiving side that are not present
   on the sending side. For version 1.6.4 I have changed the behaviour
   to match more closely what most people seem to expect of this option */
static void delete_files(struct file_list *flist)
{
  struct file_list *local_file_list;
  int i, j;

  if (cvs_exclude)
    add_cvs_excludes();

  if (io_error) {
	  fprintf(FINFO,"IO error encountered - skipping file deletion\n");
	  return;
  }

  for (j=0;j<flist->count;j++) {
	  char *name = f_name(flist->files[j]);

	  if (!S_ISDIR(flist->files[j]->mode)) continue;

	  if (strlen(name)<2 || strcmp(name+strlen(name)-2,"/.")!=0) continue;

	  if (delete_already_done(flist, j)) continue;

	  if (!(local_file_list = send_file_list(-1,1,&name)))
		  continue;

	  if (verbose > 1)
		  fprintf(FINFO,"deleting in %s\n", name);

	  for (i=local_file_list->count-1;i>=0;i--) {
		  if (!local_file_list->files[i]->basename) continue;
		  if (-1 == flist_find(flist,local_file_list->files[i])) {
			  delete_one(local_file_list->files[i]);
		  }    
	  }
	  flist_free(local_file_list);
  }
}

static char *cleanup_fname;

void exit_cleanup(int code)
{
