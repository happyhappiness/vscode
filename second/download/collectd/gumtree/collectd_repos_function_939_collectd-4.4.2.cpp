static void counters_map_set(STRUCT_COUNTERS_INFO *newcounters,
			     unsigned int index,
			     STRUCT_COUNTERS *counters)
{
	/* Want to set counter (iptables-restore) */

	memcpy(&newcounters->counters[index], counters,
		sizeof(STRUCT_COUNTERS));

	DEBUGP_C("SET\n");
}