static int as_read(void) {
  kern_return_t status;
  io_iterator_t iterator;
  io_object_t io_obj;
  CFMutableDictionaryRef prop_dict;
  CFTypeRef property;

  char type[128];
  char inst[128];
  int value_int;
  double value_double;
  if (!io_master_port || (io_master_port == MACH_PORT_NULL))
    return (-1);

  status = IOServiceGetMatchingServices(
      io_master_port, IOServiceNameMatching("IOHWSensor"), &iterator);
  if (status != kIOReturnSuccess) {
    ERROR("IOServiceGetMatchingServices failed: %s", mach_error_string(status));
    return (-1);
  }

  while ((io_obj = IOIteratorNext(iterator))) {
    prop_dict = NULL;
    status = IORegistryEntryCreateCFProperties(
        io_obj, &prop_dict, kCFAllocatorDefault, kNilOptions);
    if (status != kIOReturnSuccess) {
      DEBUG("IORegistryEntryCreateCFProperties failed: %s",
            mach_error_string(status));
      continue;
    }

    /* Copy the sensor type. */
    property = NULL;
    if (!CFDictionaryGetValueIfPresent(prop_dict, CFSTR("type"), &property))
      continue;
    if (CFGetTypeID(property) != CFStringGetTypeID())
      continue;
    if (!CFStringGetCString(property, type, sizeof(type),
                            kCFStringEncodingASCII))
      continue;
    type[sizeof(type) - 1] = '\0';

    /* Copy the sensor location. This will be used as `instance'. */
    property = NULL;
    if (!CFDictionaryGetValueIfPresent(prop_dict, CFSTR("location"), &property))
      continue;
    if (CFGetTypeID(property) != CFStringGetTypeID())
      continue;
    if (!CFStringGetCString(property, inst, sizeof(inst),
                            kCFStringEncodingASCII))
      continue;
    inst[sizeof(inst) - 1] = '\0';
    for (int i = 0; i < 128; i++) {
      if (inst[i] == '\0')
        break;
      else if (isalnum(inst[i]))
        inst[i] = (char)tolower(inst[i]);
      else
        inst[i] = '_';
    }

    /* Get the actual value. Some computation, based on the `type'
     * is neccessary. */
    property = NULL;
    if (!CFDictionaryGetValueIfPresent(prop_dict, CFSTR("current-value"),
                                       &property))
      continue;
    if (CFGetTypeID(property) != CFNumberGetTypeID())
      continue;
    if (!CFNumberGetValue(property, kCFNumberIntType, &value_int))
      continue;

    /* Found e.g. in the 1.5GHz PowerBooks */
    if (strcmp(type, "temperature") == 0) {
      value_double = ((double)value_int) / 65536.0;
      sstrncpy(type, "temperature", sizeof(type));
    } else if (strcmp(type, "temp") == 0) {
      value_double = ((double)value_int) / 10.0;
      sstrncpy(type, "temperature", sizeof(type));
    } else if (strcmp(type, "fanspeed") == 0) {
      value_double = ((double)value_int) / 65536.0;
      sstrncpy(type, "fanspeed", sizeof(type));
    } else if (strcmp(type, "voltage") == 0) {
      /* Leave this to the battery plugin. */
      continue;
    } else if (strcmp(type, "adc") == 0) {
      value_double = ((double)value_int) / 10.0;
      sstrncpy(type, "fanspeed", sizeof(type));
    } else {
      DEBUG("apple_sensors: Read unknown sensor type: %s", type);
      value_double = (double)value_int;
    }

    as_submit(type, inst, value_double);

    CFRelease(prop_dict);
    IOObjectRelease(io_obj);
  } /* while (iterator) */

  IOObjectRelease(iterator);

  return (0);
}