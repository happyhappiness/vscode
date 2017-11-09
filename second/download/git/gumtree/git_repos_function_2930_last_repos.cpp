static void
print_variable (const char *var_ptr, size_t var_len)
{
  fwrite (var_ptr, var_len, 1, stdout);
  putchar ('\n');
}