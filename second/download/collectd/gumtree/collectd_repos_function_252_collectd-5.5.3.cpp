static int mh_create (const oconfig_item_t *ci, void **user_data) /* {{{ */
{
  mh_match_t *m;
  int i;

  m = (mh_match_t *) malloc (sizeof (*m));
  if (m == NULL)
  {
    ERROR ("mh_create: malloc failed.");
    return (-ENOMEM);
  }
  memset (m, 0, sizeof (*m));

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("Match", child->key) == 0)
      mh_config_match (child, m);
    else
      ERROR ("hashed match: No such config option: %s", child->key);
  }

  if (m->matches_num == 0)
  {
    sfree (m->matches);
    sfree (m);
    ERROR ("hashed match: No matches were configured. Not creating match.");
    return (-1);
  }

  *user_data = m;
  return (0);
}