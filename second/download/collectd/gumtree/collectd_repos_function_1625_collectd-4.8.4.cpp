static void
subtract_counters(STRUCT_COUNTERS *answer,
		  const STRUCT_COUNTERS *a,
		  const STRUCT_COUNTERS *b)
{
	answer->pcnt = a->pcnt - b->pcnt;
	answer->bcnt = a->bcnt - b->bcnt;
}