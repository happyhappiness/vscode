    total_size += st.st_size;

  return &file;
}


static void send_file_name(int f,struct file_list *flist,
			   int recurse,char *fname)
{
  struct file_struct *file;

  file = make_file(recurse,fname);

  if (!file) return;
  
  if (flist->count >= flist->malloced) {
    flist->malloced += 100;
    flist->files = (struct file_struct *)realloc(flist->files,
						 sizeof(flist->files[0])*
						 flist->malloced);
    if (!flist->files)
      out_of_memory("send_file_name");
  }

  flist->files[flist->count++] = *file;    

