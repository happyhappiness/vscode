void Curl_fileinfo_dtor(void *user, void *element)
{
  struct curl_fileinfo *finfo = element;
  (void) user;
  if(!finfo)
    return;

  Curl_safefree(finfo->b_data);

  free(finfo);
}