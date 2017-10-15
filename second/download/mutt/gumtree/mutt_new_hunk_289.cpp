  }

  safe_fclose (&f);
  FREE (&linebuf);
}

static int dup_hash_dec (HASH *dup_hash, char *s)
{
  struct hash_elem *elem;
  uintptr_t count;

  elem = hash_find_elem (dup_hash, s);
  if (!elem)
    return -1;

  count = (uintptr_t)elem->data;
  if (count <= 1)
  {
    hash_delete (dup_hash, s, NULL, NULL);
    return 0;
  }

  count--;
  elem->data = (void *)count;
  return count;
}

static int dup_hash_inc (HASH *dup_hash, char *s)
{
  struct hash_elem *elem;
  uintptr_t count;

  elem = hash_find_elem (dup_hash, s);
  if (!elem)
  {
    count = 1;
    hash_insert (dup_hash, s, (void *)count);
    return count;
  }

  count = (uintptr_t)elem->data;
  count++;
  elem->data = (void *)count;
  return count;
}

static void shrink_histfile (void)
{
  char tmpfname[_POSIX_PATH_MAX];
  FILE *f, *tmp = NULL;
  int n[HC_LAST] = { 0 };
  int line, hclass, read;
  char *linebuf = NULL, *p;
  size_t buflen;
  int regen_file = 0;
  HASH *dup_hashes[HC_LAST] = { 0 };

  if ((f = fopen (HistFile, "r")) == NULL)
    return;

  if (option (OPTHISTREMOVEDUPS))
    for (hclass = 0; hclass < HC_LAST; hclass++)
      dup_hashes[hclass] = hash_create (MAX (10, SaveHist * 2), MUTT_HASH_STRDUP_KEYS);

  line = 0;
  while ((linebuf = mutt_read_line (linebuf, &buflen, f, &line, 0)) != NULL)
  {
    if (sscanf (linebuf, "%d:%n", &hclass, &read) < 1 || read == 0 ||
        *(p = linebuf + strlen (linebuf) - 1) != '|' || hclass < 0)
    {
      mutt_error (_("Bad history file format (line %d)"), line);
      goto cleanup;
    }
    /* silently ignore too high class (probably newer mutt) */
    if (hclass >= HC_LAST)
      continue;
    *p = '\0';
    if (option (OPTHISTREMOVEDUPS) &&
        (dup_hash_inc (dup_hashes[hclass], linebuf + read) > 1))
    {
      regen_file = 1;
      continue;
    }
    n[hclass]++;
  }

  if (!regen_file)
    for(hclass = HC_FIRST; hclass < HC_LAST; hclass++)
      if (n[hclass] > SaveHist)
      {
        regen_file = 1;
        break;
      }

  if (regen_file)
  {
    mutt_mktemp (tmpfname, sizeof (tmpfname));
    if ((tmp = safe_fopen (tmpfname, "w+")) == NULL)
    {
      mutt_perror (tmpfname);
      goto cleanup;
    }
    rewind (f);
    line = 0;
    while ((linebuf = mutt_read_line (linebuf, &buflen, f, &line, 0)) != NULL)
    {
      if (sscanf (linebuf, "%d:%n", &hclass, &read) < 1 || read == 0 ||
          *(p = linebuf + strlen (linebuf) - 1) != '|' || hclass < 0)
      {
        mutt_error (_("Bad history file format (line %d)"), line);
        goto cleanup;
      }
      if (hclass >= HC_LAST)
	continue;
      *p = '\0';
      if (option (OPTHISTREMOVEDUPS) &&
          (dup_hash_dec (dup_hashes[hclass], linebuf + read) > 0))
        continue;
      *p = '|';
      if (n[hclass]-- <= SaveHist)
        fprintf (tmp, "%s\n", linebuf);
    }
  }

cleanup:
