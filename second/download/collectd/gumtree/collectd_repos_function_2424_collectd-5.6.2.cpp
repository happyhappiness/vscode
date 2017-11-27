static int fc_bit_jump_destroy(void **user_data) /* {{{ */
{
  if (user_data != NULL) {
    free(*user_data);
    *user_data = NULL;
  }

  return (0);
}