char *
#ifdef _LIBC
/* Make these definitions weak in libc, so POSIX programs can redefine
   these names if they don't use our functions, and still use
   regcomp/regexec below without link errors.  */
weak_function
#endif
re_comp (s)
    const char *s;
{
  reg_errcode_t ret;

  if (!s)
    {
      if (!re_comp_buf.buffer)
	return gettext ("No previous regular expression");
      return 0;
    }

  if (!re_comp_buf.buffer)
    {
      re_comp_buf.buffer = (unsigned char *) malloc (200);	/* __MEM_CHECKED__ */
      if (re_comp_buf.buffer == NULL)
        return gettext (re_error_msgid[(int) REG_ESPACE]);
      re_comp_buf.allocated = 200;

      re_comp_buf.fastmap = (char *) malloc (1 << BYTEWIDTH);	/* __MEM_CHECKED__ */
      if (re_comp_buf.fastmap == NULL)
	return gettext (re_error_msgid[(int) REG_ESPACE]);
    }

  /* Since `re_exec' always passes NULL for the `regs' argument, we
     don't need to initialize the pattern buffer fields which affect it.  */

  /* Match anchors at newlines.  */
  re_comp_buf.newline_anchor = 1;

  ret = regex_compile (s, strlen (s), re_syntax_options, &re_comp_buf);

  if (!ret)
    return NULL;

  /* Yes, we're discarding `const' here if !HAVE_LIBINTL.  */
  return (char *) gettext (re_error_msgid[(int) ret]);
}