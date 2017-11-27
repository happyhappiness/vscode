static int mh_destroy(void **user_data) /* {{{ */
{
  mh_match_t *mh;

  if ((user_data == NULL) || (*user_data == NULL))
    return 0;

  mh = *user_data;
  sfree(mh->matches);
  sfree(mh);

  return 0;
}