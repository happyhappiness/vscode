EXPORT int
pcre_info(const pcre *argument_re, int *optptr, int *first_byte)
{
real_pcre internal_re;
const real_pcre *re = (const real_pcre *)argument_re;
if (re == NULL) return PCRE_ERROR_NULL;
if (re->magic_number != MAGIC_NUMBER)
  {
  re = try_flipped(re, &internal_re, NULL, NULL);
  if (re == NULL) return PCRE_ERROR_BADMAGIC;
  }
if (optptr != NULL) *optptr = (int)(re->options & PUBLIC_OPTIONS);
if (first_byte != NULL)
  *first_byte = ((re->options & PCRE_FIRSTSET) != 0)? re->first_byte :
     ((re->options & PCRE_STARTLINE) != 0)? -1 : -2;
return re->top_bracket;
}