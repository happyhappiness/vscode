int
regcomp(regex_t *preg, const char *pattern, int cflags)
{
const char *errorptr;
int erroffset;
int options = 0;

if ((cflags & REG_ICASE) != 0) options |= PCRE_CASELESS;
if ((cflags & REG_NEWLINE) != 0) options |= PCRE_MULTILINE;

preg->re_pcre = pcre_compile(pattern, options, &errorptr, &erroffset, NULL);
preg->re_erroffset = erroffset;

if (preg->re_pcre == NULL) return pcre_posix_error_code(errorptr);

preg->re_nsub = pcre_info(preg->re_pcre, NULL, NULL);
return 0;
}