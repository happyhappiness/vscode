int
Curl_gsk_secure_soc_open(gsk_handle my_env_handle,
                         gsk_handle * my_session_handle)

{
  struct Curl_gsk_descriptor * p;
  gsk_handle h;
  int rc;

  if(!my_env_handle)
    return GSK_INVALID_HANDLE;
  if(!my_session_handle)
    return GSK_OS400_ERROR_INVALID_POINTER;
  h = ((struct Curl_gsk_descriptor *) my_env_handle)->h;
  if(!(p = (struct Curl_gsk_descriptor *) malloc(sizeof *p)))
    return GSK_INSUFFICIENT_STORAGE;
  p->strlist = (struct gskstrlist *) NULL;
  if((rc = gsk_secure_soc_open(h, &p->h)) != GSK_OK)
    free(p);
  else
    *my_session_handle = (gsk_handle) p;
  return rc;
}