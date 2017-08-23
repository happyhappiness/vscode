static int regrepeat(const char* p)
{
  int count = 0;
  const char* scan;
  const char* opnd;

  scan = reginput;
  opnd = OPERAND(p);
  switch (OP(p)) {
    case ANY:
      count = int(strlen(scan));
      scan += count;
      break;
    case EXACTLY:
      while (*opnd == *scan) {
        count++;
        scan++;
      }
      break;
    case ANYOF:
      while (*scan != '\0' && strchr(opnd, *scan) != 0) {
        count++;
        scan++;
      }
      break;
    case ANYBUT:
      while (*scan != '\0' && strchr(opnd, *scan) == 0) {
        count++;
        scan++;
      }
      break;
    default: // Oh dear.  Called inappropriately.
      // RAISE Error, SYM(RegularExpression), SYM(Internal_Error),
      printf("cm RegularExpression::find(): Internal error.\n");
      return 0;
  }
  reginput = scan;
  return (count);
}