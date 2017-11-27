static int fbh_read_file (fbhash_t *h) /* {{{ */
{
  FILE *fh;
  char buffer[4096];
  struct flock fl;
  c_avl_tree_t *tree;
  int status;

  fh = fopen (h->filename, "r");
  if (fh == NULL)
    return (-1);

  memset (&fl, 0, sizeof (fl));
  fl.l_type = F_RDLCK;
  fl.l_whence = SEEK_SET;
  fl.l_start = 0;
  fl.l_len = 0; /* == entire file */
  /* TODO: Lock file? -> fcntl */

  status = fcntl (fileno (fh), F_SETLK, &fl);
  if (status != 0)
  {
    fclose (fh);
    return (-1);
  }

  tree = c_avl_create ((void *) strcmp);
  if (tree == NULL)
  {
    fclose (fh);
    return (-1);
  }

  /* Read `fh' into `tree' */
  while (fgets (buffer, sizeof (buffer), fh) != NULL) /* {{{ */
  {
    size_t len;
    char *key;
    char *value;

    char *key_copy;
    char *value_copy;

    buffer[sizeof (buffer) - 1] = 0;
    len = strlen (buffer);

    /* Remove trailing newline characters. */
    while ((len > 0)
        && ((buffer[len - 1] == '\n') || (buffer[len - 1] == '\r')))
    {
      len--;
      buffer[len] = 0;
    }

    /* Seek first non-space character */
    key = buffer;
    while ((*key != 0) && isspace ((int) *key))
      key++;

    /* Skip empty lines and comments */
    if ((key[0] == 0) || (key[0] == '#'))
      continue;

    /* Seek first colon */
    value = strchr (key, ':');
    if (value == NULL)
      continue;

    /* Null-terminate `key'. */
    *value = 0;
    value++;

    /* Skip leading whitespace */
    while ((*value != 0) && isspace ((int) *value))
      value++;

    /* Skip lines without value */
    if (value[0] == 0)
      continue;

    key_copy = strdup (key);
    value_copy = strdup (value);

    if ((key_copy == NULL) || (value_copy == NULL))
    {
      free (key_copy);
      free (value_copy);
      continue;
    }

    status = c_avl_insert (tree, key_copy, value_copy);
    if (status != 0)
    {
      free (key_copy);
      free (value_copy);
      continue;
    }

    DEBUG ("utils_fbhash: fbh_read_file: key = %s; value = %s;",
        key, value);
  } /* }}} while (fgets) */

  fclose (fh);

  fbh_free_tree (h->tree);
  h->tree = tree;

  return (0);
}