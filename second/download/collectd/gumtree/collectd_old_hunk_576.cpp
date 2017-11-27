    free (ci_copy);
    return (NULL);
  }

  if (ci_orig->values_num > 0) /* {{{ */
  {
    int i;

    ci_copy->values = (oconfig_value_t *) calloc (ci_orig->values_num,
	sizeof (*ci_copy->values));
    if (ci_copy->values == NULL)
    {
      fprintf (stderr, "calloc failed.\n");
      free (ci_copy->key);
      free (ci_copy);
      return (NULL);
    }
    ci_copy->values_num = ci_orig->values_num;

    for (i = 0; i < ci_copy->values_num; i++)
    {
       ci_copy->values[i].type = ci_orig->values[i].type;
       if (ci_copy->values[i].type == OCONFIG_TYPE_STRING)
       {
	 ci_copy->values[i].value.string
	   = strdup (ci_orig->values[i].value.string);
	 if (ci_copy->values[i].value.string == NULL)
	 {
	   fprintf (stderr, "strdup failed.\n");
	   oconfig_free (ci_copy);
	   return (NULL);
	 }
