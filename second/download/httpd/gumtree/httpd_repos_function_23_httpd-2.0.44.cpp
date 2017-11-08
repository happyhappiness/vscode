static void err(char *s) 
{
  perror(s);
  exit(errno);
}