int
re_match (struct re_pattern_buffer *bufp,
	  const char *string,
	  int length,
	  int start,
	  struct re_registers *regs)
{
  return re_search_stub (bufp, string, length, start, 0, length, regs, 1);
}