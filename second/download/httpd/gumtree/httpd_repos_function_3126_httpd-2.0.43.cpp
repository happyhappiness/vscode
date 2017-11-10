static BOOL
set_start_bits(const uschar *code, uschar *start_bits, BOOL caseless,
  compile_data *cd)
{
register int c;

/* This next statement and the later reference to dummy are here in order to
trick the optimizer of the IBM C compiler for OS/2 into generating correct
code. Apparently IBM isn't going to fix the problem, and we would rather not
disable optimization (in this module it actually makes a big difference, and
the pcre module can use all the optimization it can get). */

volatile int dummy;

do
  {
  const uschar *tcode = code + 3;
  BOOL try_next = TRUE;

  while (try_next)
    {
    /* If a branch starts with a bracket or a positive lookahead assertion,
    recurse to set bits from within them. That's all for this branch. */

    if ((int)*tcode >= OP_BRA || *tcode == OP_ASSERT)
      {
      if (!set_start_bits(tcode, start_bits, caseless, cd))
        return FALSE;
      try_next = FALSE;
      }

    else switch(*tcode)
      {
      default:
      return FALSE;

      /* Skip over extended extraction bracket number */

      case OP_BRANUMBER:
      tcode += 3;
      break;

      /* Skip over lookbehind and negative lookahead assertions */

      case OP_ASSERT_NOT:
      case OP_ASSERTBACK:
      case OP_ASSERTBACK_NOT:
      do tcode += (tcode[1] << 8) + tcode[2]; while (*tcode == OP_ALT);
      tcode += 3;
      break;

      /* Skip over an option setting, changing the caseless flag */

      case OP_OPT:
      caseless = (tcode[1] & PCRE_CASELESS) != 0;
      tcode += 2;
      break;

      /* BRAZERO does the bracket, but carries on. */

      case OP_BRAZERO:
      case OP_BRAMINZERO:
      if (!set_start_bits(++tcode, start_bits, caseless, cd))
        return FALSE;
      dummy = 1;
      do tcode += (tcode[1] << 8) + tcode[2]; while (*tcode == OP_ALT);
      tcode += 3;
      break;

      /* Single-char * or ? sets the bit and tries the next item */

      case OP_STAR:
      case OP_MINSTAR:
      case OP_QUERY:
      case OP_MINQUERY:
      set_bit(start_bits, tcode[1], caseless, cd);
      tcode += 2;
      break;

      /* Single-char upto sets the bit and tries the next */

      case OP_UPTO:
      case OP_MINUPTO:
      set_bit(start_bits, tcode[3], caseless, cd);
      tcode += 4;
      break;

      /* At least one single char sets the bit and stops */

      case OP_EXACT:       /* Fall through */
      tcode++;

      case OP_CHARS:       /* Fall through */
      tcode++;

      case OP_PLUS:
      case OP_MINPLUS:
      set_bit(start_bits, tcode[1], caseless, cd);
      try_next = FALSE;
      break;

      /* Single character type sets the bits and stops */

      case OP_NOT_DIGIT:
      for (c = 0; c < 32; c++)
        start_bits[c] |= ~cd->cbits[c+cbit_digit];
      try_next = FALSE;
      break;

      case OP_DIGIT:
      for (c = 0; c < 32; c++)
        start_bits[c] |= cd->cbits[c+cbit_digit];
      try_next = FALSE;
      break;

      case OP_NOT_WHITESPACE:
      for (c = 0; c < 32; c++)
        start_bits[c] |= ~cd->cbits[c+cbit_space];
      try_next = FALSE;
      break;

      case OP_WHITESPACE:
      for (c = 0; c < 32; c++)
        start_bits[c] |= cd->cbits[c+cbit_space];
      try_next = FALSE;
      break;

      case OP_NOT_WORDCHAR:
      for (c = 0; c < 32; c++)
        start_bits[c] |= ~cd->cbits[c+cbit_word];
      try_next = FALSE;
      break;

      case OP_WORDCHAR:
      for (c = 0; c < 32; c++)
        start_bits[c] |= cd->cbits[c+cbit_word];
      try_next = FALSE;
      break;

      /* One or more character type fudges the pointer and restarts, knowing
      it will hit a single character type and stop there. */

      case OP_TYPEPLUS:
      case OP_TYPEMINPLUS:
      tcode++;
      break;

      case OP_TYPEEXACT:
      tcode += 3;
      break;

      /* Zero or more repeats of character types set the bits and then
      try again. */

      case OP_TYPEUPTO:
      case OP_TYPEMINUPTO:
      tcode += 2;               /* Fall through */

      case OP_TYPESTAR:
      case OP_TYPEMINSTAR:
      case OP_TYPEQUERY:
      case OP_TYPEMINQUERY:
    