    have to replicate this bracket up to that many times. If brastackptr is
    0 this is an unmatched bracket which will generate an error, but take care
    not to try to access brastack[-1] when computing the length and restoring
    the branch_extra value. */

    case ')':
    length += 3;
      {
      int minval = 1;
      int maxval = 1;
      int duplength;

      if (brastackptr > 0)
        {
        duplength = length - brastack[--brastackptr];
        branch_extra = bralenstack[brastackptr];
        }
      else duplength = 0;

      /* Leave ptr at the final char; for read_repeat_counts this happens
      automatically; for the others we need an increment. */

      if ((c = ptr[1]) == '{' && is_counted_repeat(ptr+2, &compile_block))
        {
        ptr = read_repeat_counts(ptr+2, &minval, &maxval, errorptr,
          &compile_block);
        if (*errorptr != NULL) goto PCRE_ERROR_RETURN;
        }
      else if (c == '*') { minval = 0; maxval = -1; ptr++; }
      else if (c == '+') { maxval = -1; ptr++; }
      else if (c == '?') { minval = 0; ptr++; }

      /* If the minimum is zero, we have to allow for an OP_BRAZERO before the
      group, and if the maximum is greater than zero, we have to replicate
      maxval-1 times; each replication acquires an OP_BRAZERO plus a nesting
      bracket set - hence the 7. */

      if (minval == 0)
        {
        length++;
        if (maxval > 0) length += (maxval - 1) * (duplength + 7);
        }

      /* When the minimum is greater than zero, 1 we have to replicate up to
      minval-1 times, with no additions required in the copies. Then, if
      there is a limited maximum we have to replicate up to maxval-1 times
      allowing for a BRAZERO item before each optional copy and nesting
      brackets for all but one of the optional copies. */

      else
        {
        length += (minval - 1) * duplength;
        if (maxval > minval)   /* Need this test as maxval=-1 means no limit */
          length += (maxval - minval) * (duplength + 7) - 6;
        }
      }
    continue;

    /* Non-special character. For a run of such characters the length required
    is the number of characters + 2, except that the maximum run length is 255.
    We won't get a skipped space or a non-data escape or the start of a #
    comment as the first character, so the length can't be zero. */

    NORMAL_CHAR:
    default:
    length += 2;
    runlength = 0;
    do
      {
      if ((options & PCRE_EXTENDED) != 0)
        {
        if ((compile_block.ctypes[c] & ctype_space) != 0) continue;
        if (c == '#')
          {
          /* The space before the ; is to avoid a warning on a silly compiler
          on the Macintosh. */
          while ((c = *(++ptr)) != 0 && c != NEWLINE) ;
          continue;
          }
        }

      /* Backslash may introduce a data char or a metacharacter; stop the
      string before the latter. */

      if (c == '\\')
        {
        const uschar *saveptr = ptr;
        c = check_escape(&ptr, errorptr, bracount, options, FALSE,
          &compile_block);
        if (*errorptr != NULL) goto PCRE_ERROR_RETURN;
        if (c < 0) { ptr = saveptr; break; }

#ifdef SUPPORT_UTF8
        if (c > 127 && (options & PCRE_UTF8) != 0)
          {
          int i;
          for (i = 0; i < sizeof(utf8_table1)/sizeof(int); i++)
            if (c <= utf8_table1[i]) break;
          runlength += i;
          }
#endif
        }

      /* Ordinary character or single-char escape */

      runlength++;
      }

    /* This "while" is the end of the "do" above. */

    while (runlength < MAXLIT &&
      (compile_block.ctypes[c = *(++ptr)] & ctype_meta) == 0);

    ptr--;
    length += runlength;
    continue;
    }
  }

length += 4;    /* For final KET and END */

if (length > 65539)
  {
  *errorptr = ERR20;
  return NULL;
  }

/* Compute the size of data block needed and get it, either from malloc or
externally provided function. We specify "code[0]" in the offsetof() expression
rather than just "code", because it has been reported that one broken compiler
fails on "code" because it is also an independent variable. It should make no
difference to the value of the offsetof(). */

size = length + offsetof(real_pcre, code[0]);
re = (real_pcre *)(pcre_malloc)(size);

if (re == NULL)
  {
  *errorptr = ERR21;
  return NULL;
  }

/* Put in the magic number, and save the size, options, and table pointer */

re->magic_number = MAGIC_NUMBER;
re->size = size;
re->options = options;
re->tables = tables;

/* Set up a starting, non-extracting bracket, then compile the expression. On
error, *errorptr will be set non-NULL, so we don't need to look at the result
of the function here. */

ptr = (const uschar *)pattern;
code = re->code;
*code = OP_BRA;
bracount = 0;
(void)compile_regex(options, -1, &bracount, &code, &ptr, errorptr, FALSE, 0,
  &reqchar, &countlits, &compile_block);
re->top_bracket = bracount;
re->top_backref = top_backref;

/* If not reached end of pattern on success, there's an excess bracket. */

if (*errorptr == NULL && *ptr != 0) *errorptr = ERR22;

/* Fill in the terminating state and check for disastrous overflow, but
if debugging, leave the test till after things are printed out. */

*code++ = OP_END;

#ifndef DEBUG
if (code - re->code > length) *errorptr = ERR23;
#endif

/* Give an error if there's back reference to a non-existent capturing
subpattern. */

if (top_backref > re->top_bracket) *errorptr = ERR15;

/* Failed to compile */

if (*errorptr != NULL)
  {
  (pcre_free)(re);
  PCRE_ERROR_RETURN:
  *erroroffset = ptr - (const uschar *)pattern;
  return NULL;
  }

/* If the anchored option was not passed, set flag if we can determine that the
pattern is anchored by virtue of ^ characters or \A or anything else (such as
starting with .* when DOTALL is set).

Otherwise, see if we can determine what the first character has to be, because
that speeds up unanchored matches no end. If not, see if we can set the
PCRE_STARTLINE flag. This is helpful for multiline matches when all branches
start with ^. and also when all branches start with .* for non-DOTALL matches.
*/

if ((options & PCRE_ANCHORED) == 0)
  {
  int temp_options = options;
  if (is_anchored(re->code, &temp_options))
    re->options |= PCRE_ANCHORED;
  else
    {
    int ch = find_firstchar(re->code, &temp_options);
    if (ch >= 0)
      {
      re->first_char = ch;
      re->options |= PCRE_FIRSTSET;
      }
    else if (is_startline(re->code))
      re->options |= PCRE_STARTLINE;
    }
  }

/* Save the last required character if there are at least two literal
characters on all paths, or if there is no first character setting. */

if (reqchar >= 0 && (countlits > 1 || (re->options & PCRE_FIRSTSET) == 0))
  {
  re->req_char = reqchar;
  re->options |= PCRE_REQCHSET;
  }

/* Print out the compiled data for debugging */

#ifdef DEBUG

printf("Length = %d top_bracket = %d top_backref = %d\n",
  length, re->top_bracket, re->top_backref);

if (re->options != 0)
  {
  printf("%s%s%s%s%s%s%s%s%s\n",
    ((re->options & PCRE_ANCHORED) != 0)? "anchored " : "",
    ((re->options & PCRE_CASELESS) != 0)? "caseless " : "",
    ((re->options & PCRE_ICHANGED) != 0)? "case state changed " : "",
    ((re->options & PCRE_EXTENDED) != 0)? "extended " : "",
    ((re->options & PCRE_MULTILINE) != 0)? "multiline " : "",
    ((re->options & PCRE_DOTALL) != 0)? "dotall " : "",
