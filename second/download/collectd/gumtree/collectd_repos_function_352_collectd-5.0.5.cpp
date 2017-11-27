static counter_t disk_calc_time_incr (counter_t delta_time, counter_t delta_ops)
{
	double avg_time = ((double) delta_time) / ((double) delta_ops);
	double avg_time_incr = CDTIME_T_TO_DOUBLE (interval_g) * avg_time;

	return ((counter_t) (avg_time_incr + .5));
}