oconfig_item_t *oconfig_clone (const oconfig_item_t *ci_orig)
{
  oconfig_item_t *ci_copy;

  ci_copy = (oconfig_item_t *) malloc (sizeof (*ci_copy));
  if (ci_copy == NULL)
  {
    fprintf (stderr, "malloc failed.\n");
    return (NULL);
  }
  memset (ci_copy, 0, sizeof (*ci_copy));
  ci_copy->values = NULL;
  ci_copy->parent = NULL;
  ci_copy->children = NULL;

  ci_copy->key = strdup (ci_orig->key);
  if (ci_copy->key == NULL)
  {
    fprintf (stderr, "strdup failed.\n");
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
       }
       else /* ci_copy->values[i].type != OCONFIG_TYPE_STRING) */
       {
	 ci_copy->values[i].value = ci_orig->values[i].value;
       }
    }
  } /* }}} if (ci_orig->values_num > 0) */

  if (ci_orig->children_num > 0) /* {{{ */
  {
    int i;

    ci_copy->children = (oconfig_item_t *) calloc (ci_orig->children_num,
	sizeof (*ci_copy->children));
    if (ci_copy->children == NULL)
    {
      fprintf (stderr, "calloc failed.\n");
      oconfig_free (ci_copy);
      return (NULL);
    }
    ci_copy->children_num = ci_orig->children_num;

    for (i = 0; i < ci_copy->children_num; i++)
    {
      oconfig_item_t *child;
      
      child = oconfig_clone (ci_orig->children + i);
      if (child == NULL)
      {
	oconfig_free (ci_copy);
	return (NULL);
      }
      child->parent = ci_copy;
      ci_copy->children[i] = *child;
      free (child);
    } /* for (i = 0; i < ci_copy->children_num; i++) */
  } /* }}} if (ci_orig->children_num > 0) */

  return (ci_copy);
}