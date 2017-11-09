static void
note_variable (const char *var_ptr, size_t var_len)
{
  char *string = xmemdupz (var_ptr, var_len);

  string_list_append (&variables_set, string);
}