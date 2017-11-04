void out_of_memory(char *str)
{
  fprintf(FERROR,"ERROR: out of memory in %s\n",str);
  exit_cleanup(1);
}