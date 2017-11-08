static int
find_fixedlength(uschar *code, int options)
{
int length = -1;

register int branchlength = 0;
register uschar *cc = code + 3;

/* Scan along the opcodes for this branch. If we get to the end of the
branch, check the length against that of the other branches. */

for (;;)
  {
  int d;
  register int op = *cc;
  if (op >= OP_BRA) op = OP_BRA;

  switch (op)
    {
    case OP_BRA:
    case OP_ONCE:
    case OP_COND:
    d = find_fixedlength(cc, options);
    if (d < 0) return -1;
    branchlength += d;
    do cc += (cc[1] << 8) + cc[2]; while (*cc == OP_ALT);
    cc += 3;
    break;

    /* Reached end of a branch; if it's a ket it is the end of a nested
    call. If it's ALT it is an alternation in a nested call. If it is
    END it's the end of the outer call. All can be handled by the same code. */

    case OP_ALT:
    case OP_KET:
    case OP_KETRMAX:
    case OP_KETRMIN:
    case OP_END:
    if (length < 0) length = branchlength;
      else if (length != branchlength) return -1;
    if (*cc != OP_ALT) return length;
    cc += 3;
    branchlength = 0;
    break;

    /* Skip over assertive subpatterns */

    case OP_ASSERT:
    case OP_ASSERT_NOT:
    case OP_ASSERTBACK:
    case OP_ASSERTBACK_NOT:
    do cc += (cc[1] << 8) + cc[2]; while (*cc == OP_ALT);
    cc += 3;
    break;

    /* Skip over things that don't match chars */

    case OP_REVERSE:
    case OP_BRANUMBER:
    case OP_CREF:
    cc++;
    /* Fall through */

    case OP_OPT:
    cc++;
    /* Fall through */

    case OP_SOD:
    case OP_EOD:
    case OP_EODN:
    case OP_CIRC:
    case OP_DOLL:
    case OP_NOT_WORD_BOUNDARY:
    case OP_WORD_BOUNDARY:
    cc++;
    break;

    /* Handle char strings. In UTF-8 mode we must count characters, not bytes.
    This requires a scan of the string, unfortunately. We assume valid UTF-8
    strings, so all we do is reduce the length by one for byte whose bits are
    10xxxxxx. */

    case OP_CHARS:
    branchlength += *(++cc);
#ifdef SUPPORT_UTF8
    for (d = 1; d <= *cc; d++)
      if ((cc[d] & 0xc0) == 0x80) branchlength--;
#endif
    cc += *cc + 1;
    break;

    /* Handle exact repetitions */

    case OP_EXACT:
    case OP_TYPEEXACT:
    branchlength += (cc[1] << 8) + cc[2];
    cc += 4;
    break;

    /* Handle single-char matchers */

    case OP_NOT_DIGIT:
    case OP_DIGIT:
    case OP_NOT_WHITESPACE:
    case OP_WHITESPACE:
    case OP_NOT_WORDCHAR:
    case OP_WORDCHAR:
    case OP_ANY:
    branchlength++;
    cc++;
    break;


    /* Check a class for variable quantification */

    case OP_CLASS:
    cc += 33;

    switch (*cc)
      {
      case OP_CRSTAR:
      case OP_CRMINSTAR:
      case OP_CRQUERY:
      case OP_CRMINQUERY:
      return -1;

      case OP_CRRANGE:
      case OP_CRMINRANGE:
      if ((cc[1] << 8) + cc[2] != (cc[3] << 8) + cc[4]) return -1;
      branchlength += (cc[1] << 8) + cc[2];
      cc += 5;
      break;

      default:
      branchlength++;
      }
    break;

    /* Anything else is variable length */

    default:
    return -1;
    }
  }
/* Control never gets here */
}