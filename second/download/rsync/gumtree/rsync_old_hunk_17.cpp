oom:
  out_of_memory("do_cmd");
  return 0; /* not reached */
}


void do_server_sender(int argc,char *argv[])
{
  int i;
  char *dir = argv[0];
  struct file_list *flist;

