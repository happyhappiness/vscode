void plugin_read_all (void)
{
	if(record_statistics) {
		plugin_update_internal_statistics ();
	}
	uc_check_timeout ();

	return;
}