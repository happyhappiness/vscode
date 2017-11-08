static void delete_metalink_resource(metalink_resource *res)
{
  if(res == NULL) {
    return;
  }
  Curl_safefree(res->url);
  Curl_safefree(res);
}