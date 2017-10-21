  else
    l2 = read_byte(f);

  bzero((char *)file,sizeof(*file));

  file->name = (char *)malloc(l1+l2+1);
  if (!file->name) out_of_memory("receive_file_entry 1");

  strncpy(file->name,lastname,l1);
  read_buf(f,file->name+l1,l2);
  file->name[l1+l2] = 0;

  file->length = (off_t)read_int(f);
