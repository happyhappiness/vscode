  *f_in = from_child_pipe[0];
  *f_out = to_child_pipe[1];
  
  return pid;
}


void out_of_memory(char *str)
{
  fprintf(FERROR,"out of memory in %s\n",str);
  exit_cleanup(1);
}



int set_modtime(char *fname,time_t modtime)
