static void counters_map_set(STRUCT_COUNTERS_INFO *newcounters,
                             unsigned int idx, STRUCT_COUNTERS *counters)
{
	/* Want to set counter (iptables-restore) */

	memcpy(&newcounters->counters[idx], counters,
		sizeof(STRUCT_COUNTERS));

	DEBUGP_C("SET\n");
}