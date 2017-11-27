void hostname_set(char const *hostname) {
  char *h = strdup(hostname);
  if (h == NULL)
    return;

  sfree(hostname_g);
  hostname_g = h;
}