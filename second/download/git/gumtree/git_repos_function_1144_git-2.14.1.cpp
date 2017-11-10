static int git_wcwidth(ucs_char_t ch)
{
	/*
	 * Sorted list of non-overlapping intervals of non-spacing characters,
	 */
#include "unicode_width.h"

	/* test for 8-bit control characters */
	if (ch == 0)
		return 0;
	if (ch < 32 || (ch >= 0x7f && ch < 0xa0))
		return -1;

	/* binary search in table of non-spacing characters */
	if (bisearch(ch, zero_width, sizeof(zero_width)
				/ sizeof(struct interval) - 1))
		return 0;

	/* binary search in table of double width characters */
	if (bisearch(ch, double_width, sizeof(double_width)
				/ sizeof(struct interval) - 1))
		return 2;

	return 1;
}