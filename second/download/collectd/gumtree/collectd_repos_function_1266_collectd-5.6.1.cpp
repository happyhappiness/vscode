static int mv_config_add_data_source (mv_match_t *m, /* {{{ */
    oconfig_item_t *ci)
{
  size_t new_data_sources_num;
  char **temp;

  /* Check number of arbuments. */
  if (ci->values_num < 1)
  {
    ERROR ("`value' match: `%s' needs at least one argument.",
        ci->key);
    return (-1);
  }

  /* Check type of arguments */
  for (int i = 0; i < ci->values_num; i++)
  {
    if (ci->values[i].type == OCONFIG_TYPE_STRING)
      continue;

    ERROR ("`value' match: `%s' accepts only string arguments "
        "(argument %i is a %s).",
        ci->key, i + 1,
        (ci->values[i].type == OCONFIG_TYPE_BOOLEAN)
        ? "truth value" : "number");
    return (-1);
  }

  /* Allocate space for the char pointers */
  new_data_sources_num = m->data_sources_num + ((size_t) ci->values_num);
  temp = realloc (m->data_sources,
      new_data_sources_num * sizeof (char *));
  if (temp == NULL)
  {
    ERROR ("`value' match: realloc failed.");
    return (-1);
  }
  m->data_sources = temp;

  /* Copy the strings, allocating memory as needed. */
  for (int i = 0; i < ci->values_num; i++)
  {
    /* If we get here, there better be memory for us to write to. */
    assert (m->data_sources_num < new_data_sources_num);

    size_t j = m->data_sources_num;
    m->data_sources[j] = sstrdup (ci->values[i].value.string);
    if (m->data_sources[j] == NULL)
    {
      ERROR ("`value' match: sstrdup failed.");
      continue;
    }
    m->data_sources_num++;
  }

  return (0);
}