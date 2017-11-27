static void ntpd_submit_reach (char *type, char *type_inst, uint8_t reach,
		gauge_t value)
{
	if (!(reach & 1))
		value = NAN;

	ntpd_submit (type, type_inst, value);
}