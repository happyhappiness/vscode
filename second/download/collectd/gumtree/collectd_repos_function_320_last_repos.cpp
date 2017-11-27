static void submit_capacity(char const *plugin_instance, /* {{{ */
                            gauge_t capacity_charged, gauge_t capacity_full,
                            gauge_t capacity_design) {
  if (report_percent && (capacity_charged > capacity_full))
    return;
  if (report_degraded && (capacity_full > capacity_design))
    return;

  if (report_percent) {
    gauge_t capacity_max;

    if (report_degraded)
      capacity_max = capacity_design;
    else
      capacity_max = capacity_full;

    battery_submit2(plugin_instance, "percent", "charged",
                    100.0 * capacity_charged / capacity_max);
    battery_submit2(plugin_instance, "percent", "discharged",
                    100.0 * (capacity_full - capacity_charged) / capacity_max);

    if (report_degraded)
      battery_submit2(plugin_instance, "percent", "degraded",
                      100.0 * (capacity_design - capacity_full) / capacity_max);
  } else if (report_degraded) /* && !report_percent */
  {
    battery_submit2(plugin_instance, "capacity", "charged", capacity_charged);
    battery_submit2(plugin_instance, "capacity", "discharged",
                    (capacity_full - capacity_charged));
    battery_submit2(plugin_instance, "capacity", "degraded",
                    (capacity_design - capacity_full));
  } else /* !report_percent && !report_degraded */
  {
    battery_submit(plugin_instance, "capacity", capacity_charged);
  }
}