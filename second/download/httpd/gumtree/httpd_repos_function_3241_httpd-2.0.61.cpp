void
regfree(regex_t *preg)
{
(pcre_free)(preg->re_pcre);
}