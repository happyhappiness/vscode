static int aquaero_read (void)
{
	aq5_data_t aq_data;
	aq5_settings_t aq_sett;
	char *err_msg = NULL;
	char type_instance[DATA_MAX_NAME_LEN];
	int i;

	if (libaquaero5_poll(conf_device, &aq_data, &err_msg) < 0)
	{
		char errbuf[1024];
		ERROR ("aquaero plugin: Failed to poll device \"%s\": %s (%s)",
				conf_device ? conf_device : "default", err_msg,
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	if (libaquaero5_getsettings(conf_device, &aq_sett, &err_msg) < 0)
	{
		char errbuf[1024];
		ERROR ("aquaero plugin: Failed to get settings "
				"for device \"%s\": %s (%s)",
				conf_device ? conf_device : "default", err_msg,
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	/* CPU Temperature sensor */
	aquaero_submit("temperature", "cpu", aq_data.cpu_temp[0]);

	/* Temperature sensors */
	aquaero_submit_array("temperature", "sensor", aq_data.temp,
			AQ5_NUM_TEMP);

	/* Virtual temperature sensors */
	aquaero_submit_array("temperature", "virtual", aq_data.vtemp,
			AQ5_NUM_VIRT_SENSORS);

	/* Software temperature sensors */
	aquaero_submit_array("temperature", "software", aq_data.stemp,
			AQ5_NUM_SOFT_SENSORS);

	/* Other temperature sensors */
	aquaero_submit_array("temperature", "other", aq_data.otemp,
			AQ5_NUM_OTHER_SENSORS);

	/* Fans */
	for (i = 0; i < AQ5_NUM_FAN; i++)
	{
		if ((aq_sett.fan_data_source[i] == NONE)
				|| (aq_data.fan_vrm_temp[i] != AQ5_FLOAT_UNDEF))
			continue;

		snprintf (type_instance, sizeof (type_instance),
				"fan%d", i + 1);

		aquaero_submit ("fanspeed", type_instance,
				aq_data.fan_rpm[i]);
		aquaero_submit ("percent", type_instance,
				aq_data.fan_duty[i]);
		aquaero_submit ("voltage", type_instance,
				aq_data.fan_voltage[i]);
		aquaero_submit ("current", type_instance,
				aq_data.fan_current[i]);

		/* Report the voltage reglator module (VRM) temperature with a
		 * different type instance. */
		snprintf (type_instance, sizeof (type_instance),
				"fan%d-vrm", i + 1);
		aquaero_submit ("temperature", type_instance,
				aq_data.fan_vrm_temp[i]);
	}

	/* Flow sensors */
	aquaero_submit_array("flow", "sensor", aq_data.flow, AQ5_NUM_FLOW);

	/* Liquid level */
	aquaero_submit_array("percent", "waterlevel",
			aq_data.level, AQ5_NUM_LEVEL);

	return (0);
}