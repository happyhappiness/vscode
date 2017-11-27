void tail_match_destroy (cu_tail_match_t *obj)
{
  int i;

  if (obj == NULL)
    return;

  if (obj->tail != NULL)
  {
    cu_tail_destroy (obj->tail);
    obj->tail = NULL;
  }

  for (i = 0; i < obj->matches_num; i++)
  {
    cu_tail_match_match_t *match = obj->matches + i;
    if (match->match != NULL)
    {
      match_destroy (match->match);
      match->match = NULL;
    }

    if ((match->user_data != NULL)
	&& (match->free != NULL))
      (*match->free) (match->user_data);
    match->user_data = NULL;
  }

  sfree (obj->matches);
  sfree (obj);
}