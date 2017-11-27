int tail_match_add_match (cu_tail_match_t *obj, cu_match_t *match,
    int (*submit_match) (cu_match_t *match, void *user_data),
    void *user_data,
    void (*free_user_data) (void *user_data))
{
  cu_tail_match_match_t *temp;

  temp = (cu_tail_match_match_t *) realloc (obj->matches,
      sizeof (cu_tail_match_match_t) * (obj->matches_num + 1));
  if (temp == NULL)
    return (-1);

  obj->matches = temp;
  obj->matches_num++;

  DEBUG ("tail_match_add_match interval %lf", CDTIME_T_TO_DOUBLE(((cu_tail_match_simple_t *)user_data)->interval));
  temp = obj->matches + (obj->matches_num - 1);

  temp->match = match;
  temp->user_data = user_data;
  temp->submit = submit_match;
  temp->free = free_user_data;

  return (0);
}