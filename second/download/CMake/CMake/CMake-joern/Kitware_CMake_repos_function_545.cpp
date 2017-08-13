int
archive_write_set_format_filter_by_ext_def(struct archive *a, const char *filename, const char * def_ext)
{
  int names_index = get_array_index(filename);
  
  if (names_index < 0)
    names_index = get_array_index(def_ext);
  
  if (names_index >= 0)
  {  
    int format_state = (names[names_index].format)(a);
    if (format_state == ARCHIVE_OK)
      return ((names[names_index].filter)(a));
    else
      return format_state;
  }    

  archive_set_error(a, EINVAL, "No such format '%s'", filename);
  a->state = ARCHIVE_STATE_FATAL;
  return (ARCHIVE_FATAL);
}