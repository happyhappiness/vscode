static int parse_url_file(const char *filename)
{
  FILE *f;
  int filetime;
  char buf[200];

  num_handles = 0;
  blacklist_num_sites = 0;
  blacklist_num_servers = 0;

  f = fopen(filename, "rb");
  if(!f)
    return 0;

  while(!feof(f)) {
    if(fscanf(f, "%d %s\n", &filetime, buf)) {
      urltime[num_handles] = filetime;
      urlstring[num_handles] = strdup(buf);
      num_handles++;
      continue;
    }

    if(fscanf(f, "blacklist_site %s\n", buf)) {
      site_blacklist[blacklist_num_sites] = strdup(buf);
      blacklist_num_sites++;
      continue;
    }

    break;
  }
  fclose(f);

  site_blacklist[blacklist_num_sites] = NULL;
  server_blacklist[blacklist_num_servers] = NULL;
  return num_handles;
}