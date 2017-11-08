static size_t my_fread(void *buffer, size_t sz, size_t nmemb, void *userp)
{
  ssize_t rc;
  struct InStruct *in=(struct InStruct *)userp;

  rc = read(in->fd, buffer, sz*nmemb);
  if(rc < 0)
    /* since size_t is unsigned we can't return negative values fine */
    return 0;
  return (size_t)rc;
}