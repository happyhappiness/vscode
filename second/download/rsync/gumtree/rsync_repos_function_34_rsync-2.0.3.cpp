void send_exclude_list(int f)
{
  int i;
  if (exclude_list) 
    for (i=0;exclude_list[i];i++) {
      int l = strlen(exclude_list[i]);
      if (l == 0) continue;
      write_int(f,l);
      write_buf(f,exclude_list[i],l);
    }    
  write_int(f,0);
}