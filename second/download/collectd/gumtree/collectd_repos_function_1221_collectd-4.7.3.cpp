static int plugin_compare_read_func (const void *arg0, const void *arg1)
{
	const read_func_t *rf0;
	const read_func_t *rf1;

	rf0 = arg0;
	rf1 = arg1;

	if (rf0->rf_next_read.tv_sec < rf1->rf_next_read.tv_sec)
		return (-1);
	else if (rf0->rf_next_read.tv_sec > rf1->rf_next_read.tv_sec)
		return (1);
	else if (rf0->rf_next_read.tv_nsec < rf1->rf_next_read.tv_nsec)
		return (-1);
	else if (rf0->rf_next_read.tv_nsec > rf1->rf_next_read.tv_nsec)
		return (1);
	else
		return (0);
}