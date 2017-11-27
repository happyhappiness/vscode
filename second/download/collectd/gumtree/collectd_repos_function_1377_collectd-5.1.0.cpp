cu_match_t *match_create_simple (const char *regex,
				 const char *excluderegex, int match_ds_type)
{
  cu_match_value_t *user_data;
  cu_match_t *obj;

  user_data = (cu_match_value_t *) malloc (sizeof (cu_match_value_t));
  if (user_data == NULL)
    return (NULL);
  memset (user_data, '\0', sizeof (cu_match_value_t));
  user_data->ds_type = match_ds_type;

  obj = match_create_callback (regex, excluderegex,
			       default_callback, user_data);
  if (obj == NULL)
  {
    sfree (user_data);
    return (NULL);
  }

  obj->flags |= UTILS_MATCH_FLAGS_FREE_USER_DATA;

  return (obj);
}