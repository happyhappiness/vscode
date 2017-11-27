static int cdbi_result_get_field (dbi_result res, /* {{{ */
    unsigned int index, char *buffer, size_t buffer_size)
{
  unsigned short src_type;

  src_type = dbi_result_get_field_type_idx (res, index);
  if (src_type == DBI_TYPE_ERROR)
  {
    ERROR ("dbi plugin: cdbi_result_get: "
        "dbi_result_get_field_type_idx failed.");
    return (-1);
  }

  if (src_type == DBI_TYPE_INTEGER)
  {
    long long value;

    value = dbi_result_get_longlong_idx (res, index);
    ssnprintf (buffer, buffer_size, "%lli", value);
  }
  else if (src_type == DBI_TYPE_DECIMAL)
  {
    double value;

    value = dbi_result_get_double_idx (res, index);
    ssnprintf (buffer, buffer_size, "%63.15g", value);
  }
  else if (src_type == DBI_TYPE_STRING)
  {
    const char *value;
    
    value = dbi_result_get_string_idx (res, index);
    if (value == NULL)
      sstrncpy (buffer, "", buffer_size);
    else if (strcmp ("ERROR", value) == 0)
      return (-1);
    else
      sstrncpy (buffer, value, buffer_size);
  }
  else
  {
    ERROR ("dbi plugin: cdbi_result_get: Don't know how to handle "
        "source type %hu.", src_type);
    return (-1);
  }

  return (0);
}