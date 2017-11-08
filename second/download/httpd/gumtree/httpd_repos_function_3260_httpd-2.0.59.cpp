int
pcre_exec(const pcre *external_re, const pcre_extra *external_extra,
  const char *subject, int length, int start_offset, int options, int *offsets,
  int offsetcount)
{
int resetcount, ocount;
int first_char = -1;
int req_char = -1;
int req_char2 = -1;
unsigned long int ims = 0;
match_data match_block;
const uschar *start_bits = NULL;
const uschar *start_match = (const uschar *)subject + start_offset;
const uschar *end_subject;
const uschar *req_char_ptr = start_match - 1;
const real_pcre *re = (const real_pcre *)external_re;
const real_pcre_extra *extra = (const real_pcre_extra *)external_extra;
BOOL using_temporary_offsets = FALSE;
BOOL anchored;
BOOL startline;

if ((options & ~PUBLIC_EXEC_OPTIONS) != 0) return PCRE_ERROR_BADOPTION;

if (re == NULL || subject == NULL ||
   (offsets == NULL && offsetcount > 0)) return PCRE_ERROR_NULL;
if (re->magic_number != MAGIC_NUMBER) return PCRE_ERROR_BADMAGIC;

anchored = ((re->options | options) & PCRE_ANCHORED) != 0;
startline = (re->options & PCRE_STARTLINE) != 0;

match_block.start_pattern = re->code;
match_block.start_subject = (const uschar *)subject;
match_block.end_subject = match_block.start_subject + length;
end_subject = match_block.end_subject;

match_block.endonly = (re->options & PCRE_DOLLAR_ENDONLY) != 0;
match_block.utf8 = (re->options & PCRE_UTF8) != 0;

match_block.notbol = (options & PCRE_NOTBOL) != 0;
match_block.noteol = (options & PCRE_NOTEOL) != 0;
match_block.notempty = (options & PCRE_NOTEMPTY) != 0;

match_block.errorcode = PCRE_ERROR_NOMATCH;     /* Default error */

match_block.lcc = re->tables + lcc_offset;
match_block.ctypes = re->tables + ctypes_offset;

/* The ims options can vary during the matching as a result of the presence
of (?ims) items in the pattern. They are kept in a local variable so that
restoring at the exit of a group is easy. */

ims = re->options & (PCRE_CASELESS|PCRE_MULTILINE|PCRE_DOTALL);

/* If the expression has got more back references than the offsets supplied can
hold, we get a temporary bit of working store to use during the matching.
Otherwise, we can use the vector supplied, rounding down its size to a multiple
of 3. */

ocount = offsetcount - (offsetcount % 3);

if (re->top_backref > 0 && re->top_backref >= ocount/3)
  {
  ocount = re->top_backref * 3 + 3;
  match_block.offset_vector = (int *)(pcre_malloc)(ocount * sizeof(int));
  if (match_block.offset_vector == NULL) return PCRE_ERROR_NOMEMORY;
  using_temporary_offsets = TRUE;
  DPRINTF(("Got memory to hold back references\n"));
  }
else match_block.offset_vector = offsets;

match_block.offset_end = ocount;
match_block.offset_max = (2*ocount)/3;
match_block.offset_overflow = FALSE;

/* Compute the minimum number of offsets that we need to reset each time. Doing
this makes a huge difference to execution time when there aren't many brackets
in the pattern. */

resetcount = 2 + re->top_bracket * 2;
if (resetcount > offsetcount) resetcount = ocount;

/* Reset the working variable associated with each extraction. These should
never be used unless previously set, but they get saved and restored, and so we
initialize them to avoid reading uninitialized locations. */

if (match_block.offset_vector != NULL)
  {
  register int *iptr = match_block.offset_vector + ocount;
  register int *iend = iptr - resetcount/2 + 1;
  while (--iptr >= iend) *iptr = -1;
  }

/* Set up the first character to match, if available. The first_char value is
never set for an anchored regular expression, but the anchoring may be forced
at run time, so we have to test for anchoring. The first char may be unset for
an unanchored pattern, of course. If there's no first char and the pattern was
studied, there may be a bitmap of possible first characters. */

if (!anchored)
  {
  if ((re->options & PCRE_FIRSTSET) != 0)
    {
    first_char = re->first_char;
    if ((ims & PCRE_CASELESS) != 0) first_char = match_block.lcc[first_char];
    }
  else
    if (!startline && extra != NULL &&
      (extra->options & PCRE_STUDY_MAPPED) != 0)
        start_bits = extra->start_bits;
  }

/* For anchored or unanchored matches, there may be a "last known required
character" set. If the PCRE_CASELESS is set, implying that the match starts
caselessly, or if there are any changes of this flag within the regex, set up
both cases of the character. Otherwise set the two values the same, which will
avoid duplicate testing (which takes significant time). This covers the vast
majority of cases. It will be suboptimal when the case flag changes in a regex
and the required character in fact is caseful. */

if ((re->options & PCRE_REQCHSET) != 0)
  {
  req_char = re->req_char;
  req_char2 = ((re->options & (PCRE_CASELESS | PCRE_ICHANGED)) != 0)?
    (re->tables + fcc_offset)[req_char] : req_char;
  }

/* Loop for handling unanchored repeated matching attempts; for anchored regexs
the loop runs just once. */

do
  {
  int rc;
  register int *iptr = match_block.offset_vector;
  register int *iend = iptr + resetcount;

  /* Reset the maximum number of extractions we might see. */

  while (iptr < iend) *iptr++ = -1;

  /* Advance to a unique first char if possible */

  if (first_char >= 0)
    {
    if ((ims & PCRE_CASELESS) != 0)
      while (start_match < end_subject &&
             match_block.lcc[*start_match] != first_char)
        start_match++;
    else
      while (start_match < end_subject && *start_match != first_char)
        start_match++;
    }

  /* Or to just after \n for a multiline match if possible */

  else if (startline)
    {
    if (start_match > match_block.start_subject + start_offset)
      {
      while (start_match < end_subject && start_match[-1] != NEWLINE)
        start_match++;
      }
    }

  /* Or to a non-unique first char after study */

  else if (start_bits != NULL)
    {
    while (start_match < end_subject)
      {
      register int c = *start_match;
      if ((start_bits[c/8] & (1 << (c&7))) == 0) start_match++; else break;
      }
    }

#ifdef DEBUG  /* Sigh. Some compilers never learn. */
  printf(">>>> Match against: ");
  pchars(start_match, end_subject - start_match, TRUE, &match_block);
  printf("\n");
#endif

  /* If req_char is set, we know that that character must appear in the subject
  for the match to succeed. If the first character is set, req_char must be
  later in the subject; otherwise the test starts at the match point. This
  optimization can save a huge amount of backtracking in patterns with nested
  unlimited repeats that aren't going to match. We don't know what the state of
  case matching may be when this character is hit, so test for it in both its
  cases if necessary. However, the different cased versions will not be set up
  unless PCRE_CASELESS was given or the casing state changes within the regex.
  Writing separate code makes it go faster, as does using an autoincrement and
  backing off on a match. */

  if (req_char >= 0)
    {
    register const uschar *p = start_match + ((first_char >= 0)? 1 : 0);

    /* We don't need to repeat the search if we haven't yet reached the
    place we found it at last time. */

    if (p > req_char_ptr)
      {
      /* Do a single test if no case difference is set up */

      if (req_char == req_char2)
        {
        while (p < end_subject)
          {
          if (*p++ == req_char) { p--; break; }
          }
        }

      /* Otherwise test for either case */

      else
        {
        while (p < end_subject)
          {
          register int pp = *p++;
          if (pp == req_char || pp == req_char2) { p--; break; }
          }
        }

      /* If we can't find the required character, break the matching loop */

      if (p >= end_subject) break;

      /* If we have found the required character, save the point where we
      found it, so that we don't search again next time round the loop if
      the start hasn't passed this character yet. */

      req_char_ptr = p;
      }
    }

  /* When a match occurs, substrings will be set for all internal extractions;
  we just need to set up the whole thing as substring 0 before returning. If
  there were too many extractions, set the return code to zero. In the case
  where we had to get some local store to hold offsets for backreferences, copy
  those back references that we can. In this case there need not be overflow
  if certain parts of the pattern were not used. */

  match_block.start_match = start_match;
  if (!match(start_match, re->code, 2, &match_block, ims, NULL, match_isgroup))
    continue;

  /* Copy the offset information from temporary store if necessary */

  if (using_temporary_offsets)
    {
    if (offsetcount >= 4)
      {
      memcpy(offsets + 2, match_block.offset_vector + 2,
        (offsetcount - 2) * sizeof(int));
      DPRINTF(("Copied offsets from temporary memory\n"));
      }
    if (match_block.end_offset_top > offsetcount)
      match_block.offset_overflow = TRUE;

    DPRINTF(("Freeing temporary memory\n"));
    (pcre_free)(match_block.offset_vector);
    }

  rc = match_block.offset_overflow? 0 : match_block.end_offset_top/2;

  if (offsetcount < 2) rc = 0; else
    {
    offsets[0] = start_match - match_block.start_subject;
    offsets[1] = match_block.end_match_ptr - match_block.start_subject;
    }

  DPRINTF((">>>> returning %d\n", rc));
  return rc;
  }

/* This "while" is the end of the "do" above */

while (!anchored &&
       match_block.errorcode == PCRE_ERROR_NOMATCH &&
       start_match++ < end_subject);

if (using_temporary_offsets)
  {
  DPRINTF(("Freeing temporary memory\n"));
  (pcre_free)(match_block.offset_vector);
  }

DPRINTF((">>>> returning %d\n", match_block.errorcode));

return match_block.errorcode;
}