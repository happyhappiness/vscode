static int mec_create (const oconfig_item_t *ci, void **user_data) /* {{{ */
{
  mec_match_t *m;

  m = (mec_match_t *) malloc (sizeof (*m));
  if (m == NULL)
  {
    ERROR ("mec_create: malloc failed.");
    return (-ENOMEM);
  }
  memset (m, 0, sizeof (*m));

  if (ci->children_num != 0)
  {
    ERROR ("empty_counter match: This match does not take any additional "
        "configuration.");
  }

  *user_data = m;
  return (0);
}