int km_expand_key (char *s, size_t len, struct keymap_t *map)
{
  size_t l;
  int p = 0;

  if (!map)
    return (0);

  FOREVER
  {
    strfcpy (s, km_keyname (map->keys[p]), len);
    len -= (l = mutt_strlen (s));

    if (++p >= map->len || !len)
      return (1);

    s += l;
  }

  /* not reached */
}