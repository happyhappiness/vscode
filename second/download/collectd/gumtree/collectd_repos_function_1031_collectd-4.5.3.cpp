static void counters_map_zeroed(STRUCT_COUNTERS_INFO *newcounters,
				STRUCT_REPLACE *repl,
				unsigned int index,
				unsigned int mappos,
				STRUCT_COUNTERS *counters)
{
	/* Original read: X.
	 * Atomic read on replacement: X + Y.
	 * Currently in kernel: Z.
	 * Want in kernel: Y + Z.
	 * => Add in Y.
	 * => Add in (replacement read - original read).
	 */
	subtract_counters(&newcounters->counters[index],
			  &repl->counters[mappos],
			  counters);
	DEBUGP_C("ZEROED => mappos %u\n", mappos);
}