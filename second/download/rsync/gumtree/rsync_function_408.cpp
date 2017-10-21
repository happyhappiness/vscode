void overflow(char *str)
{
  fprintf(FERROR,"ERROR: buffer overflow in %s\n",str);
  exit_cleanup(1);
}