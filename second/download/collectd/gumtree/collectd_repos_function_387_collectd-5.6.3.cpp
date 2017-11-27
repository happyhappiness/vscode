static void get_via_io_power_sources(double *ret_charge, /* {{{ */
                                     double *ret_current, double *ret_voltage) {
  CFTypeRef ps_raw;
  CFArrayRef ps_array;
  int ps_array_len;
  CFDictionaryRef ps_dict;
  CFTypeRef ps_obj;

  double temp_double;

  ps_raw = IOPSCopyPowerSourcesInfo();
  ps_array = IOPSCopyPowerSourcesList(ps_raw);
  ps_array_len = CFArrayGetCount(ps_array);

  DEBUG("ps_array_len == %i", ps_array_len);

  for (int i = 0; i < ps_array_len; i++) {
    ps_obj = CFArrayGetValueAtIndex(ps_array, i);
    ps_dict = IOPSGetPowerSourceDescription(ps_raw, ps_obj);

    if (ps_dict == NULL) {
      DEBUG("IOPSGetPowerSourceDescription failed.");
      continue;
    }

    if (CFGetTypeID(ps_dict) != CFDictionaryGetTypeID()) {
      DEBUG("IOPSGetPowerSourceDescription did not return a CFDictionaryRef");
      continue;
    }

    /* FIXME: Check if this is really an internal battery */

    if (isnan(*ret_charge)) {
      /* This is the charge in percent. */
      temp_double = dict_get_double(ps_dict, kIOPSCurrentCapacityKey);
      if (!isnan((temp_double)) && (temp_double >= 0.0) &&
          (temp_double <= 100.0))
        *ret_charge = temp_double;
    }

    if (isnan(*ret_current)) {
      temp_double = dict_get_double(ps_dict, kIOPSCurrentKey);
      if (!isnan(temp_double))
        *ret_current = temp_double / 1000.0;
    }

    if (isnan(*ret_voltage)) {
      temp_double = dict_get_double(ps_dict, kIOPSVoltageKey);
      if (!isnan(temp_double))
        *ret_voltage = temp_double / 1000.0;
    }
  }

  CFRelease(ps_array);
  CFRelease(ps_raw);
}