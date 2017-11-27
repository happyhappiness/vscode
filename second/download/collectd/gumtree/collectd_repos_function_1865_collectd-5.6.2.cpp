static void data_free_all(mb_data_t *data) /* {{{ */
{
  mb_data_t *next;

  if (data == NULL)
    return;

  next = data->next;
  data_free_one(data);

  data_free_all(next);
}