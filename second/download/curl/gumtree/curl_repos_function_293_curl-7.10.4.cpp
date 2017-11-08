static char *
create_hostcache_id(char *server, int port, ssize_t *entry_len)
{
  char *id = NULL;

  /* Get the length of the new entry id */
  *entry_len = *entry_len +      /* Hostname length */
               1 +               /* The ':' seperator */
               _num_chars(port); /* The number of characters the port will take up */
  
  /* Allocate the new entry id */
  id = malloc(*entry_len + 1);
  if (!id) {
    return NULL;
  }

  /* Create the new entry */
  /* If sprintf() doesn't return the entry length, that signals failure */
  if (sprintf(id, "%s:%d", server, port) != *entry_len) {
    /* Free the allocated id, set length to zero and return NULL */
    *entry_len = 0;
    free(id);
    return NULL;
  }

  return id;
}