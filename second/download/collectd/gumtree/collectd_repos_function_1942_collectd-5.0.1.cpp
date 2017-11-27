static void counters_nomap(STRUCT_COUNTERS_INFO *newcounters, unsigned int idx)
{
	newcounters->counters[idx] = ((STRUCT_COUNTERS) { 0, 0});
	DEBUGP_C("NOMAP => zero\n");
}