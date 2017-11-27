static void get_via_generic_iokit (double *ret_capacity_full, /* {{{ */
		double *ret_capacity_design,
		double *ret_current,
		double *ret_voltage)
{
	kern_return_t   status;
	io_iterator_t   iterator;
	io_object_t     io_obj;

	CFDictionaryRef bat_root_dict;
	CFArrayRef      bat_info_arry;
	CFIndex         bat_info_arry_len;
	CFDictionaryRef bat_info_dict;

	double temp_double;

	status = IOServiceGetMatchingServices (kIOMasterPortDefault,
			IOServiceNameMatching ("battery"),
			&iterator);
	if (status != kIOReturnSuccess)
	{
		DEBUG ("IOServiceGetMatchingServices failed.");
		return;
	}

	while ((io_obj = IOIteratorNext (iterator)))
	{
		status = IORegistryEntryCreateCFProperties (io_obj,
				(CFMutableDictionaryRef *) &bat_root_dict,
				kCFAllocatorDefault,
				kNilOptions);
		if (status != kIOReturnSuccess)
		{
			DEBUG ("IORegistryEntryCreateCFProperties failed.");
			continue;
		}

		bat_info_arry = (CFArrayRef) CFDictionaryGetValue (bat_root_dict,
				CFSTR ("IOBatteryInfo"));
		if (bat_info_arry == NULL)
		{
			CFRelease (bat_root_dict);
			continue;
		}
		bat_info_arry_len = CFArrayGetCount (bat_info_arry);

		for (CFIndex bat_info_arry_pos = 0;
				bat_info_arry_pos < bat_info_arry_len;
				bat_info_arry_pos++)
		{
			bat_info_dict = (CFDictionaryRef) CFArrayGetValueAtIndex (bat_info_arry, bat_info_arry_pos);

			if (isnan (*ret_capacity_full))
			{
				temp_double = dict_get_double (bat_info_dict, "Capacity");
				*ret_capacity_full = temp_double / 1000.0;
			}

			if (isnan (*ret_capacity_design))
			{
				temp_double = dict_get_double (bat_info_dict, "AbsoluteMaxCapacity");
				*ret_capacity_design = temp_double / 1000.0;
			}

			if (isnan (*ret_current))
			{
				temp_double = dict_get_double (bat_info_dict, "Current");
				*ret_current = temp_double / 1000.0;
			}

			if (isnan (*ret_voltage))
			{
				temp_double = dict_get_double (bat_info_dict, "Voltage");
				*ret_voltage = temp_double / 1000.0;
			}
		}

		CFRelease (bat_root_dict);
	}

	IOObjectRelease (iterator);
}