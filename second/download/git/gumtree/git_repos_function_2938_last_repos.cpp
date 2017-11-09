static void
note_variables (const char *string)
{
  string_list_init (&variables_set);
  find_variables (string, &note_variable);
  string_list_sort (&variables_set);
}