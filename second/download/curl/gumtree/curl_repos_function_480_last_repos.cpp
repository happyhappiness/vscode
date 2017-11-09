static void free_urls(void)
{
  int i;
  for(i = 0; i < num_handles; i++) {
    Curl_safefree(urlstring[i]);
  }
  for(i = 0; i < blacklist_num_servers; i++) {
    Curl_safefree(server_blacklist[i]);
  }
  for(i = 0; i < blacklist_num_sites; i++) {
    Curl_safefree(site_blacklist[i]);
  }
}