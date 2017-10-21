      fprintf(FERROR,"deleting directory %s\n",f->name);      
    }
  }
}


static void delete_files(struct file_list *flist)
{
  struct file_list *local_file_list;
  char *dot=".";
  int i;

  if (cvs_exclude)
    add_cvs_excludes();

  if (!(local_file_list = send_file_list(-1,1,&dot)))
    return;

  for (i=local_file_list->count-1;i>=0;i--) {
    if (!local_file_list->files[i].name) continue;
    if (-1 == flist_find(flist,&local_file_list->files[i])) {
      delete_one(&local_file_list->files[i]);
    }    
  }
}

static char *cleanup_fname = NULL;

void exit_cleanup(int code)
