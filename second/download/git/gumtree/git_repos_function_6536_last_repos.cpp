void fast_export_deinit(void)
{
	if (buffer_deinit(&report_buffer))
		die_errno("error closing fast-import feedback stream");
}