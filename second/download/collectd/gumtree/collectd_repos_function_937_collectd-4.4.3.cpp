static void counters_normal_map(STRUCT_COUNTERS_INFO *newcounters,
				STRUCT_REPLACE *repl,
				unsigned int index,
				unsigned int mappos)
{
	/* Original read: X.
	 * Atomic read on replacement: X + Y.
	 * Currently in kernel: Z.
	 * Want in kernel: X + Y + Z.
	 * => Add in X + Y
	 * => Add in replacement read.
	 */
	newcounters->counters[index] = repl->counters[mappos];
	DEBUGP_C("NORMAL_MAP => mappos %u \n", mappos);
}