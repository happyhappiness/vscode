static inline long count_masked_bytes(unsigned long mask)
{
	if (sizeof(long) == 8) {
		/*
		 * Jan Achrenius on G+: microoptimized version of
		 * the simpler "(mask & ONEBYTES) * ONEBYTES >> 56"
		 * that works for the bytemasks without having to
		 * mask them first.
		 */
		/*
		 * return mask * 0x0001020304050608 >> 56;
		 *
		 * Doing it like this avoids warnings on 32-bit machines.
		 */
		long a = (REPEAT_BYTE(0x01) / 0xff + 1);
		return mask * a >> (sizeof(long) * 7);
	} else {
		/* Carl Chatfield / Jan Achrenius G+ version for 32-bit */
		/* (000000 0000ff 00ffff ffffff) -> ( 1 1 2 3 ) */
		long a = (0x0ff0001 + mask) >> 23;
		/* Fix the 1 for 00 case */
		return a & mask;
	}
}