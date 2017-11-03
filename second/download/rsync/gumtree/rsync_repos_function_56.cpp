static void delete_files(struct file_list *flist)
{
  struct file_list *local_file_list;
  char *dot=".";
  int i;

  if (cvs_exclude)
    add_cvs_excludes();

  if (!(local_file_list = send_file_list(-1,recurse,1,&dot)))
    return;

  for (i=local_file_list->count;i>=0;i--) {
    if (!local_file_list->files[i].name) continue;
    if (-1 == flist_find(flist,&local_file_list->files[i])) {
      delete_one(&local_file_list->files[i]);
    }    
  }
}