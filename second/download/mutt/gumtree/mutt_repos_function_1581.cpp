static int fetch_auth (char *line, void *data)
{
  POP_DATA *pop_data = (POP_DATA *)data;

  if (!pop_data->auth_list)
  {
    pop_data->auth_list = safe_malloc (strlen (line) + 1);
    *pop_data->auth_list = '\0';
  }
  else
  {
    safe_realloc (&pop_data->auth_list,
	    strlen (pop_data->auth_list) + strlen (line) + 2);
    strcat (pop_data->auth_list, " ");	/* __STRCAT_CHECKED__ */
  }
  strcat (pop_data->auth_list, line);	/* __STRCAT_CHECKED__ */

  return 0;
}