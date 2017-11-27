static int parse_packet (void *buffer, int buffer_len)
{
	part_header_t *header;
	int status;

	value_list_t vl = VALUE_LIST_INIT;
	char type[DATA_MAX_NAME_LEN];
	notification_t n;

	DEBUG ("network plugin: parse_packet: buffer = %p; buffer_len = %i;",
			buffer, buffer_len);

	memset (&vl, '\0', sizeof (vl));
	memset (&type, '\0', sizeof (type));
	memset (&n, '\0', sizeof (n));
	status = 0;

	while ((status == 0) && (0 < buffer_len)
			&& ((unsigned int) buffer_len > sizeof (part_header_t)))
	{
		header = (part_header_t *) buffer;

		if (ntohs (header->length) > buffer_len)
			break;
		/* Assure that this loop terminates eventually */
		if (ntohs (header->length) < 4)
			break;

		if (ntohs (header->type) == TYPE_VALUES)
		{
			status = parse_part_values (&buffer, &buffer_len,
					&vl.values, &vl.values_len);

			if (status != 0)
			{
				DEBUG ("parse_part_values failed.");
				break;
			}

			if ((vl.time > 0)
					&& (strlen (vl.host) > 0)
					&& (strlen (vl.plugin) > 0)
					&& (strlen (type) > 0)
					&& (cache_check (type, &vl) == 0))
			{
				DEBUG ("network plugin: parse_packet:"
						" dispatching values");
				plugin_dispatch_values (type, &vl);
			}
			else
			{
				DEBUG ("network plugin: parse_packet:"
						" NOT dispatching values");
			}
		}
		else if (ntohs (header->type) == TYPE_TIME)
		{
			uint64_t tmp = 0;
			status = parse_part_number (&buffer, &buffer_len, &tmp);
			if (status == 0)
			{
				vl.time = (time_t) tmp;
				n.time = (time_t) tmp;
			}
		}
		else if (ntohs (header->type) == TYPE_INTERVAL)
		{
			uint64_t tmp = 0;
			status = parse_part_number (&buffer, &buffer_len, &tmp);
			if (status == 0)
				vl.interval = (int) tmp;
		}
		else if (ntohs (header->type) == TYPE_HOST)
		{
			status = parse_part_string (&buffer, &buffer_len,
					vl.host, sizeof (vl.host));
			strncpy (n.host, vl.host, sizeof (n.host));
			n.host[sizeof (n.host) - 1] = '\0';
			DEBUG ("network plugin: parse_packet: vl.host = %s",
					vl.host);
		}
		else if (ntohs (header->type) == TYPE_PLUGIN)
		{
			status = parse_part_string (&buffer, &buffer_len,
					vl.plugin, sizeof (vl.plugin));
			strncpy (n.plugin, vl.plugin, sizeof (n.plugin));
			n.plugin[sizeof (n.plugin) - 1] = '\0';
			DEBUG ("network plugin: parse_packet: vl.plugin = %s",
					vl.plugin);
		}
		else if (ntohs (header->type) == TYPE_PLUGIN_INSTANCE)
		{
			status = parse_part_string (&buffer, &buffer_len,
					vl.plugin_instance,
					sizeof (vl.plugin_instance));
			strncpy (n.plugin_instance, vl.plugin_instance,
					sizeof (n.plugin_instance));
			n.plugin_instance[sizeof (n.plugin_instance) - 1] = '\0';
			DEBUG ("network plugin: parse_packet: "
					"vl.plugin_instance = %s",
					vl.plugin_instance);
		}
		else if (ntohs (header->type) == TYPE_TYPE)
		{
			status = parse_part_string (&buffer, &buffer_len,
					type, sizeof (type));
			strncpy (n.type, type, sizeof (n.type));
			n.type[sizeof (n.type) - 1] = '\0';
			DEBUG ("network plugin: parse_packet: type = %s",
					type);
		}
		else if (ntohs (header->type) == TYPE_TYPE_INSTANCE)
		{
			status = parse_part_string (&buffer, &buffer_len,
					vl.type_instance,
					sizeof (vl.type_instance));
			strncpy (n.type_instance, vl.type_instance,
					sizeof (n.type_instance));
			n.type_instance[sizeof (n.type_instance) - 1] = '\0';
			DEBUG ("network plugin: parse_packet: "
					"vl.type_instance = %s",
					vl.type_instance);
		}
		else if (ntohs (header->type) == TYPE_MESSAGE)
		{
			status = parse_part_string (&buffer, &buffer_len,
					n.message, sizeof (n.message));
			DEBUG ("network plugin: parse_packet: n.message = %s",
					n.message);

			if ((n.severity != NOTIF_FAILURE)
					&& (n.severity != NOTIF_WARNING)
					&& (n.severity != NOTIF_OKAY))
			{
				INFO ("network plugin: "
						"Ignoring notification with "
						"unknown severity %s.",
						n.severity);
			}
			else if (n.time <= 0)
			{
				INFO ("network plugin: "
						"Ignoring notification with "
						"time == 0.");
			}
			else if (strlen (n.message) <= 0)
			{
				INFO ("network plugin: "
						"Ignoring notification with "
						"an empty message.");
			}
			else
			{
				/*
				 * TODO: Let this do a separate thread so that
				 * no packets are lost if this takes too long.
				 */
				plugin_dispatch_notification (&n);
			}
		}
		else if (ntohs (header->type) == TYPE_SEVERITY)
		{
			uint64_t tmp = 0;
			status = parse_part_number (&buffer, &buffer_len, &tmp);
			if (status == 0)
				n.severity = (int) tmp;
		}
		else
		{
			DEBUG ("network plugin: parse_packet: Unknown part"
					" type: 0x%0hx", ntohs (header->type));
			buffer = ((char *) buffer) + ntohs (header->length);
		}
	} /* while (buffer_len > sizeof (part_header_t)) */

	return (0);
}