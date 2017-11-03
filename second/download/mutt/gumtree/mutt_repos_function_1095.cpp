reg_syntax_t
re_set_syntax (syntax)
    reg_syntax_t syntax;
{
  reg_syntax_t ret = re_syntax_options;

  re_syntax_options = syntax;
#ifdef DEBUG
  if (syntax & RE_DEBUG)
    debug = 1;
  else if (debug) /* was on but now is not */
    debug = 0;
#endif /* DEBUG */
  return ret;
}