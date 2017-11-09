int
attribute_compat_text_section
__compat_regexec (const regex_t *__restrict preg,
		  const char *__restrict string, size_t nmatch,
		  regmatch_t pmatch[], int eflags)
{
  return regexec (preg, string, nmatch, pmatch,
		  eflags & (REG_NOTBOL | REG_NOTEOL));
}