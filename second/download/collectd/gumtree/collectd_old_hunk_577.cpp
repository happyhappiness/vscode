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
