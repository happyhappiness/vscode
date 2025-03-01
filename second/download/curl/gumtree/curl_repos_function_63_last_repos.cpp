int main(int argc, char **argv)
{
  const char *name = argc > 1 ? argv[1] : "openssl";
  CURLsslset result;

  if(!strcmp("list", name)) {
    const curl_ssl_backend **list;
    int i;

    result = curl_global_sslset(-1, NULL, &list);
    assert(result == CURLSSLSET_UNKNOWN_BACKEND);

    for(i = 0; list[i]; i++)
      printf("SSL backend #%d: '%s' (ID: %d)\n",
             i, list[i]->name, list[i]->id);

    return 0;
  }
  else if(isdigit(*name)) {
    curl_sslbackend id = (curl_sslbackend)atoi(name);

    result = curl_global_sslset(id, NULL, NULL);
  }
  else
    result = curl_global_sslset(-1, name, NULL);

  if(result == CURLSSLSET_UNKNOWN_BACKEND) {
    fprintf(stderr, "Unknown SSL backend id: %s\n", name);
    return 1;
  }

  assert(result == CURLSSLSET_OK);

  printf("Version with SSL backend '%s':\n\n\t%s\n", name, curl_version());

  return 0;
}