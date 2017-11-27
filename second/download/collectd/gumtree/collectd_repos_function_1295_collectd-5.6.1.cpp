static void cldap_submit_gauge (const char *type, const char *type_instance, /* {{{ */
		gauge_t g, cldap_t *st)
{
	value_t v;
	v.gauge = g;
	cldap_submit_value (type, type_instance, v, st);
}