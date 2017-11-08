static void
print_variables (const char *string)
{
  find_variables (string, &print_variable);
}