static void free_userdata(user_data_t const *ud) /* {{{ */
{
  if (ud == NULL)
    return;

  if ((ud->data != NULL) && (ud->free_func != NULL)) {
    ud->free_func(ud->data);
  }
}