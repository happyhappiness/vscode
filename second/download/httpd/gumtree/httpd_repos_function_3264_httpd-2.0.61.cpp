static const uschar*
first_significant_code(const uschar *code, int *options, int optbit,
  BOOL optstop)
{
for (;;)
  {
  switch ((int)*code)
    {
    case OP_OPT:
    if (optbit > 0 && ((int)code[1] & optbit) != (*options & optbit))
      {
      if (optstop) return code;
      *options = (int)code[1];
      }
    code += 2;
    break;

    case OP_CREF:
    case OP_BRANUMBER:
    code += 3;
    break;

    case OP_WORD_BOUNDARY:
    case OP_NOT_WORD_BOUNDARY:
    code++;
    break;

    case OP_ASSERT_NOT:
    case OP_ASSERTBACK:
    case OP_ASSERTBACK_NOT:
    do code += (code[1] << 8) + code[2]; while (*code == OP_ALT);
    code += 3;
    break;

    default:
    return code;
    }
  }
/* Control never reaches here */
}