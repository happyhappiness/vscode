static void cr_free_data (cr_data_t *ptr) /* {{{ */
{
  if (ptr == NULL)
    return;

  ros_disconnect (ptr->connection);
  ptr->connection = NULL;

  sfree (ptr->node);
  sfree (ptr->service);
  sfree (ptr->username);
  sfree (ptr->password);

  sfree (ptr);
}