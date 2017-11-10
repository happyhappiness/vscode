int
regexec (
	const regex_t *__restrict preg,
	const char *__restrict string,
	size_t nmatch,
	regmatch_t pmatch[],
	int eflags)
{
  reg_errcode_t err;
  int start, length;

  if (eflags & ~(REG_NOTBOL | REG_NOTEOL | REG_STARTEND))
    return REG_BADPAT;

  if (eflags & REG_STARTEND)
    {
      start = pmatch[0].rm_so;
      length = pmatch[0].rm_eo;
    }
  else
    {
      start = 0;
      length = strlen (string);
    }

  __libc_lock_lock (dfa->lock);
  if (preg->no_sub)
    err = re_search_internal (preg, string, length, start, length - start,
			      length, 0, NULL, eflags);
  else
    err = re_search_internal (preg, string, length, start, length - start,
			      length, nmatch, pmatch, eflags);
  __libc_lock_unlock (dfa->lock);
  return err != REG_NOERROR;
}