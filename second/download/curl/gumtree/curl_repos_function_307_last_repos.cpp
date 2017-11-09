int
Curl_gsk_environment_open(gsk_handle * my_env_handle)

{
  struct Curl_gsk_descriptor * p;
  gsk_handle h;
  int rc;

  if(!my_env_handle)
    return GSK_OS400_ERROR_INVALID_POINTER;
  if(!(p = (struct Curl_gsk_descriptor *) malloc(sizeof *p)))
    return GSK_INSUFFICIENT_STORAGE;
  p->strlist = (struct gskstrlist *) NULL;
  if((rc = gsk_environment_open(&p->h)) != GSK_OK)
    free(p);
  else
    *my_env_handle = (gsk_handle) p;
  return rc;
}