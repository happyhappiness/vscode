pcre_extra *
pcre_study(const pcre *external_re, int options, const char **errorptr)
{
uschar start_bits[32];
real_pcre_extra *extra;
const real_pcre *re = (const real_pcre *)external_re;
compile_data compile_block;

*errorptr = NULL;

if (re == NULL || re->magic_number != MAGIC_NUMBER)
  {
  *errorptr = "argument is not a compiled regular expression";
  return NULL;
  }

if ((options & ~PUBLIC_STUDY_OPTIONS) != 0)
  {
  *errorptr = "unknown or incorrect option bit(s) set";
  return NULL;
  }

/* For an anchored pattern, or an unchored pattern that has a first char, or a
multiline pattern that matches only at "line starts", no further processing at
present. */

if ((re->options & (PCRE_ANCHORED|PCRE_FIRSTSET|PCRE_STARTLINE)) != 0)
  return NULL;

/* Set the character tables in the block which is passed around */

compile_block.lcc = re->tables + lcc_offset;
compile_block.fcc = re->tables + fcc_offset;
compile_block.cbits = re->tables + cbits_offset;
compile_block.ctypes = re->tables + ctypes_offset;

/* See if we can find a fixed set of initial characters for the pattern. */

memset(start_bits, 0, 32 * sizeof(uschar));
if (!set_start_bits(re->code, start_bits, (re->options & PCRE_CASELESS) != 0,
  &compile_block)) return NULL;

/* Get an "extra" block and put the information therein. */

extra = (real_pcre_extra *)(pcre_malloc)(sizeof(real_pcre_extra));

if (extra == NULL)
  {
  *errorptr = "failed to get memory";
  return NULL;
  }

extra->options = PCRE_STUDY_MAPPED;
memcpy(extra->start_bits, start_bits, sizeof(start_bits));

return (pcre_extra *)extra;
}