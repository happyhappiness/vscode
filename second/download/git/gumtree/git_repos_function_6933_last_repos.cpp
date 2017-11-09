int
re_search (struct re_pattern_buffer *bufp,
	   const char *string,
	   int length, int start, int range,
	   struct re_registers *regs)
{
  return re_search_stub (bufp, string, length, start, range, length, regs, 0);
}