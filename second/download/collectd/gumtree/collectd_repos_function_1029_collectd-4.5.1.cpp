static void counters_nomap(STRUCT_COUNTERS_INFO *newcounters,
			   unsigned int index)
{
	newcounters->counters[index] = ((STRUCT_COUNTERS) { 0, 0});
	DEBUGP_C("NOMAP => zero\n");
}