cu_tail_match_t *tail_match_create (const char *filename)
{
  cu_tail_match_t *obj;

  obj = (cu_tail_match_t *) malloc (sizeof (cu_tail_match_t));
  if (obj == NULL)
    return (NULL);
  memset (obj, '\0', sizeof (cu_tail_match_t));

  obj->tail = cu_tail_create (filename);
  if (obj->tail == NULL)
  {
    sfree (obj);
    return (NULL);
  }

  return (obj);
}