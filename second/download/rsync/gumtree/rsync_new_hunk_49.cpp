    }
  }
  if (buf2) free(buf2);
}


static void delete_files(struct file_list *flist)
{
  struct file_list *local_file_list;
  char *dot=".";
  int i;

  if (!(local_file_list = send_file_list(-1,recurse,1,&dot)))
    return;

  for (i=0;i<local_file_list->count;i++) {
    if (!local_file_list->files[i].name) continue;
    if (S_ISDIR(local_file_list->files[i].mode)) continue;
    if (-1 == flist_find(flist,&local_file_list->files[i])) {
      if (verbose)
	fprintf(stderr,"deleting %s\n",local_file_list->files[i].name);
      if (!dry_run) {
	if (unlink(local_file_list->files[i].name) != 0)
	  fprintf(stderr,"unlink %s : %s\n",
		  local_file_list->files[i].name,strerror(errno));
      }
    }    
  }
}

int recv_files(int f_in,struct file_list *flist,char *local_name)
{  
  int fd1,fd2;
  struct stat st;
  char *fname;
