static void delete_metalinkfile(metalinkfile *mlfile)
{
  metalink_resource *res;
  if(mlfile == NULL) {
    return;
  }
  Curl_safefree(mlfile->filename);
  delete_metalink_checksum(mlfile->checksum);
  for(res = mlfile->resource; res;) {
    metalink_resource *next;
    next = res->next;
    delete_metalink_resource(res);
    res = next;
  }
  Curl_safefree(mlfile);
}