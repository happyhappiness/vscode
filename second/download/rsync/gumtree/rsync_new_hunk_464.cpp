}



void out_of_memory(char *str)
{
  rprintf(FERROR,"ERROR: out of memory in %s\n",str);
  exit_cleanup(1);
}

void overflow(char *str)
{
  rprintf(FERROR,"ERROR: buffer overflow in %s\n",str);
  exit_cleanup(1);
}



int set_modtime(char *fname,time_t modtime)
