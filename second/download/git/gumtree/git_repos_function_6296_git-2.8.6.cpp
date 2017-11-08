static re_sub_match_last_t *
internal_function
match_ctx_add_sublast (re_sub_match_top_t *subtop, int node, int str_idx)
{
  re_sub_match_last_t *new_entry;
  if (BE (subtop->nlasts == subtop->alasts, 0))
    {
      int new_alasts = 2 * subtop->alasts + 1;
      re_sub_match_last_t **new_array = re_realloc (subtop->lasts,
						    re_sub_match_last_t *,
						    new_alasts);
      if (BE (new_array == NULL, 0))
	return NULL;
      subtop->lasts = new_array;
      subtop->alasts = new_alasts;
    }
  new_entry = calloc (1, sizeof (re_sub_match_last_t));
  if (BE (new_entry != NULL, 1))
    {
      subtop->lasts[subtop->nlasts] = new_entry;
      new_entry->node = node;
      new_entry->str_idx = str_idx;
      ++subtop->nlasts;
    }
  return new_entry;
}