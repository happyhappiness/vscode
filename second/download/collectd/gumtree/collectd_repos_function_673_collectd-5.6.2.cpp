static int cjni_match_target_destroy(void **user_data) /* {{{ */
{
  cjni_callback_info_destroy(*user_data);
  *user_data = NULL;

  return (0);
}