int
re_match_2 (struct re_pattern_buffer *bufp,
	    const char *string1, int length1,
	    const char *string2, int length2, int start,
	    struct re_registers *regs, int stop)
{
  return re_search_2_stub (bufp, string1, length1, string2, length2,
			   start, 0, regs, stop, 1);
}