static void tr_meta_data_action_destroy(tr_meta_data_action_t *act) /* {{{ */
{
  if (act == NULL)
    return;

  sfree(act->key);
  regfree(&act->re);
  sfree(act->replacement);

  if (act->next != NULL)
    tr_meta_data_action_destroy(act->next);

  sfree(act);
}