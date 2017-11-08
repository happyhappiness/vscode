static
int my_getpass(void *clientp, const char *prompt, char* buffer, int buflen )
{
  char *retbuf;
  clientp=NULL; /* prevent compiler warning */

  retbuf = getpass_r(prompt, buffer, buflen);
  if(NULL == retbuf)
    return 1;
  else
    return 0; /* success */
}