				apcups_detail->outputv = value;
			else if (strcmp ("LINEFREQ", key) == 0)
				apcups_detail->linefreq = value;
			else if (strcmp ("TIMELEFT", key) == 0)
				apcups_detail->timeleft = value;

			tokptr = strtok_r (NULL, ":", &toksaveptr);
		} /* while (tokptr != NULL) */
	}
	
	if (n < 0)
	{
		WARNING ("apcups plugin: Error reading from socket");
		return (-1);
	}

	return (0);
}

static int apcups_config (const char *key, const char *value)
{
	if (strcasecmp (key, "host") == 0)
	{
		if (conf_host != NULL)
		{
			free (conf_host);
			conf_host = NULL;
		}
		if ((conf_host = strdup (value)) == NULL)
			return (1);
	}
	else if (strcasecmp (key, "Port") == 0)
	{
		int port_tmp = atoi (value);
		if (port_tmp < 1 || port_tmp > 65535)
		{
			WARNING ("apcups plugin: Invalid port: %i", port_tmp);
			return (1);
		}
		conf_port = port_tmp;
	}
	else
	{
		return (-1);
	}
	return (0);
}

static void apc_submit_generic (char *type, char *type_inst, double value)
{
	value_t values[1];
	value_list_t vl = VALUE_LIST_INIT;

	values[0].gauge = value;

	vl.values = values;
	vl.values_len = 1;
	vl.time = time (NULL);
	strcpy (vl.host, hostname_g);
	strcpy (vl.plugin, "apcups");
	strcpy (vl.plugin_instance, "");
	strncpy (vl.type_instance, type_inst, sizeof (vl.type_instance));

	plugin_dispatch_values (type, &vl);
}

static void apc_submit (struct apc_detail_s *apcups_detail)
{
	apc_submit_generic ("apcups_voltage",    "input",   apcups_detail->linev);
	apc_submit_generic ("apcups_voltage",    "output",  apcups_detail->outputv);
	apc_submit_generic ("apcups_voltage",    "battery", apcups_detail->battv);
	apc_submit_generic ("apcups_charge",     "",        apcups_detail->bcharge);
	apc_submit_generic ("apcups_charge_pct", "",        apcups_detail->loadpct);
	apc_submit_generic ("apcups_timeleft",   "",        apcups_detail->timeleft);
	apc_submit_generic ("apcups_temp",       "",        apcups_detail->itemp);
	apc_submit_generic ("apcups_frequency",  "input",   apcups_detail->linefreq);
}

static int apcups_read (void)
{
	struct apc_detail_s apcups_detail;
	int status;

	apcups_detail.linev    =   -1.0;
	apcups_detail.outputv  =   -1.0;
