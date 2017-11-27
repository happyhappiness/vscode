static cdtime_t cna_child_get_cdtime (na_elem_t *data) /* {{{ */
{
	time_t t;

	t = (time_t) na_child_get_uint64 (data, "timestamp", /* default = */ 0);

	return (TIME_T_TO_CDTIME_T (t));
}