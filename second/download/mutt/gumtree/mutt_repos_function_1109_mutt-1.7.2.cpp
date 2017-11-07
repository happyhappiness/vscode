int
re_match (bufp, string, size, pos, regs)
     struct re_pattern_buffer *bufp;
     const char *string;
     int size, pos;
     struct re_registers *regs;
{
  int result = re_match_2_internal (bufp, NULL, 0, string, size,
				    pos, regs, size);
#ifndef REGEX_MALLOC
#ifdef C_ALLOCA
  alloca (0);
#endif
#endif
  return result;
}