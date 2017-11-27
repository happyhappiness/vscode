static int mec_create (const oconfig_item_t *ci, void **user_data) /* {{{ */
{
  if (ci->children_num != 0)
  {
    ERROR ("empty_counter match: This match does not take any additional "
        "configuration.");
  }

  *user_data = NULL;
  return (0);
}