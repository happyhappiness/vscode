cu_tail_match_t *tail_match_create (const char *filename)
{
  cu_tail_match_t *obj;

  obj = calloc (1, sizeof (*obj));
  if (obj == NULL)
    return (NULL);

  obj->tail = cu_tail_create (filename);
  if (obj->tail == NULL)
  {
    sfree (obj);
    return (NULL);
  }

  return (obj);
}