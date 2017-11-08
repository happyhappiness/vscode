static const uschar *
find_bracket(const uschar *code, BOOL utf8, int number)
{
#ifndef SUPPORT_UTF8
utf8 = utf8;               /* Stop pedantic compilers complaining */
#endif

for (;;)
  {
  register int c = *code;
  if (c == OP_END) return NULL;
  else if (c > OP_BRA)
    {
    int n = c - OP_BRA;
    if (n > EXTRACT_BASIC_MAX) n = GET2(code, 2+LINK_SIZE);
    if (n == number) return (uschar *)code;
    code += OP_lengths[OP_BRA];
    }
  else
    {
    code += OP_lengths[c];

#ifdef SUPPORT_UTF8

    /* In UTF-8 mode, opcodes that are followed by a character may be followed
    by a multi-byte character. The length in the table is a minimum, so we have
    to scan along to skip the extra bytes. All opcodes are less than 128, so we
    can use relatively efficient code. */

    if (utf8) switch(c)
      {
      case OP_CHAR:
      case OP_CHARNC:
      case OP_EXACT:
      case OP_UPTO:
      case OP_MINUPTO:
      case OP_STAR:
      case OP_MINSTAR:
      case OP_PLUS:
      case OP_MINPLUS:
      case OP_QUERY:
      case OP_MINQUERY:
      while ((*code & 0xc0) == 0x80) code++;
      break;

      /* XCLASS is used for classes that cannot be represented just by a bit
      map. This includes negated single high-valued characters. The length in
      the table is zero; the actual length is stored in the compiled code. */

      case OP_XCLASS:
      code += GET(code, 1) + 1;
      break;
      }
#endif
    }
  }
}