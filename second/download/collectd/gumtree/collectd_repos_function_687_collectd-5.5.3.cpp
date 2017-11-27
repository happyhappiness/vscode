static int mic_config (const char *key, const char *value) {
	if (temp_ignore == NULL)
		temp_ignore = ignorelist_create(1);
	if (power_ignore == NULL)
		power_ignore = ignorelist_create(1);
	if (temp_ignore == NULL || power_ignore == NULL)
		return (1);

	if (strcasecmp("ShowCPU",key) == 0)
	{
		show_cpu = IS_TRUE(value);
	}
	else if (strcasecmp("ShowCPUCores",key) == 0)
	{
		show_cpu_cores = IS_TRUE(value);
	}
	else if (strcasecmp("ShowTemperatures",key) == 0)
	{
		show_temps = IS_TRUE(value);
	}
	else if (strcasecmp("ShowMemory",key) == 0)
	{
		show_memory = IS_TRUE(value);
	}
	else if (strcasecmp("ShowPower",key) == 0)
	{
		show_power = IS_TRUE(value);
	}
	else if (strcasecmp("Temperature",key) == 0)
	{
		ignorelist_add(temp_ignore,value);
	}
	else if (strcasecmp("IgnoreSelectedTemperature",key) == 0)
	{
		int invert = 1;
		if (IS_TRUE(value))
			invert = 0;
		ignorelist_set_invert(temp_ignore,invert);
	}
	else if (strcasecmp("Power",key) == 0)
	{
		ignorelist_add(power_ignore,value);
	}
	else if (strcasecmp("IgnoreSelectedPower",key) == 0)
	{
		int invert = 1;
		if (IS_TRUE(value))
			invert = 0;
		ignorelist_set_invert(power_ignore,invert);
	}
	else
	{
		return (-1);
	}
	return (0);
}