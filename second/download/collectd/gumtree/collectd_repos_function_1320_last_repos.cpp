static int mv_destroy(void **user_data) /* {{{ */
{
  if ((user_data != NULL) && (*user_data != NULL))
    mv_free_match(*user_data);
  return 0;
}