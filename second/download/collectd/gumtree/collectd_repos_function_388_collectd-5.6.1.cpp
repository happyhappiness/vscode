static int battery_read (void) /* {{{ */
{
	gauge_t current = NAN; /* Current in A */
	gauge_t voltage = NAN; /* Voltage in V */

	/* We only get the charged capacity as a percentage from
	 * IOPowerSources. IOKit, on the other hand, only reports the full
	 * capacity. We use the two to calculate the current charged capacity. */
	gauge_t charge_rel = NAN; /* Current charge in percent */
	gauge_t capacity_charged; /* Charged capacity */
	gauge_t capacity_full = NAN; /* Total capacity */
	gauge_t capacity_design = NAN; /* Full design capacity */

#if HAVE_IOKIT_PS_IOPOWERSOURCES_H
	get_via_io_power_sources (&charge_rel, &current, &voltage);
#endif
#if HAVE_IOKIT_IOKITLIB_H
	get_via_generic_iokit (&capacity_full, &capacity_design, &current, &voltage);
#endif

	capacity_charged = charge_rel * capacity_full / 100.0;
	submit_capacity ("0", capacity_charged, capacity_full, capacity_design);

	if (!isnan (current))
		battery_submit ("0", "current", current);
	if (!isnan (voltage))
		battery_submit ("0", "voltage", voltage);

	return (0);
}