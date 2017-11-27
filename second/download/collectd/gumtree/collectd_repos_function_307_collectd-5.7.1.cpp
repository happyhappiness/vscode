int battery_read_statefs(void) {
  value_t v;
  int success = 0;

  if (parse_value_file(STATEFS_ROOT "ChargePercentage", &v, DS_TYPE_GAUGE) ==
      0) {
    battery_submit("charge", v.gauge, NULL);
    success++;
  } else if (parse_value_file(STATEFS_ROOT "Capacity", &v, DS_TYPE_GAUGE) ==
             0) {
    // Use capacity as a charge estimate if ChargePercentage is not available
    battery_submit("charge", v.gauge, NULL);
    success++;
  } else {
    WARNING("battery plugin: Neither \"" STATEFS_ROOT "ChargePercentage\" "
            "nor \"" STATEFS_ROOT "Capacity\" could be read.");
  }

  struct {
    char *path;
    char *type;
    char *type_instance;
    gauge_t factor;
  } metrics[] = {
      {STATEFS_ROOT "Current", "current", NULL, 1e-6},        // from uA to A
      {STATEFS_ROOT "Energy", "energy_wh", NULL, 1e-6},       // from uWh to Wh
      {STATEFS_ROOT "Power", "power", NULL, 1e-6},            // from uW to W
      {STATEFS_ROOT "Temperature", "temperature", NULL, 0.1}, // from 10xC to C
      {STATEFS_ROOT "TimeUntilFull", "duration", "full", 1.0},
      {STATEFS_ROOT "TimeUntilLow", "duration", "low", 1.0},
      {STATEFS_ROOT "Voltage", "voltage", NULL, 1e-6}, // from uV to V
  };

  for (size_t i = 0; i < STATIC_ARRAY_SIZE(metrics); i++) {
    if (parse_value_file(metrics[i].path, &v, DS_TYPE_GAUGE) != 0) {
      WARNING("battery plugin: Reading \"%s\" failed.", metrics[i].path);
      continue;
    }

    battery_submit(metrics[i].type, v.gauge * metrics[i].factor,
                   metrics[i].type_instance);
    success++;
  }

  if (success == 0) {
    ERROR("battery plugin: statefs backend: none of the statistics are "
          "available");
    return (-1);
  }

  return (0);
}