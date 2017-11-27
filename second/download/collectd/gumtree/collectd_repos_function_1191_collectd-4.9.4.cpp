cu_match_t *match_create_callback (const char *regex,
		int (*callback) (const char *str,
		  char * const *matches, size_t matches_num, void *user_data),
		void *user_data)
{
  cu_match_t *obj;
  int status;

  DEBUG ("utils_match: match_create_callback: regex = %s", regex);

  obj = (cu_match_t *) malloc (sizeof (cu_match_t));
  if (obj == NULL)
    return (NULL);
  memset (obj, '\0', sizeof (cu_match_t));

  status = regcomp (&obj->regex, regex, REG_EXTENDED | REG_NEWLINE);
  if (status != 0)
  {
    ERROR ("Compiling the regular expression \"%s\" failed.", regex);
    sfree (obj);
    return (NULL);
  }

  obj->callback = callback;
  obj->user_data = user_data;

  return (obj);
}