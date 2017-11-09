void Curl_fileinfo_dtor(void *user, void *element)
{
  struct fileinfo *finfo = element;
  (void) user;
  if(!finfo)
    return;

  Curl_safefree(finfo->info.b_data);

  free(finfo);
}