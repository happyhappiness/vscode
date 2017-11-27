static cache_entry_t *cache_alloc (int values_num)
{
  cache_entry_t *ce;

  ce = (cache_entry_t *) malloc (sizeof (cache_entry_t));
  if (ce == NULL)
  {
    ERROR ("utils_cache: cache_alloc: malloc failed.");
    return (NULL);
  }
  memset (ce, '\0', sizeof (cache_entry_t));
  ce->values_num = values_num;

  ce->values_gauge = (gauge_t *) calloc (values_num, sizeof (gauge_t));
  ce->values_counter = (counter_t *) calloc (values_num, sizeof (counter_t));
  if ((ce->values_gauge == NULL) || (ce->values_counter == NULL))
  {
    sfree (ce->values_gauge);
    sfree (ce->values_counter);
    sfree (ce);
    ERROR ("utils_cache: cache_alloc: calloc failed.");
    return (NULL);
  }

  return (ce);
}