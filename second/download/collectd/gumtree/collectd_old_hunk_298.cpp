
	plugin_log (SvIV (ST (0)), "%s", SvPV_nolen (ST (1)));
	XSRETURN_YES;
} /* static XS (Collectd_plugin_log) */

/*
 * Collectd::call_by_name (...).
 *
 * Call a Perl sub identified by its name passed through $Collectd::cb_name.
 */
static XS (Collectd_call_by_name)
{
