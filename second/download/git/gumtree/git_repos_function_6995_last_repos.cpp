reg_syntax_t
re_set_syntax (reg_syntax_t syntax)
{
  reg_syntax_t ret = re_syntax_options;

  re_syntax_options = syntax;
  return ret;
}