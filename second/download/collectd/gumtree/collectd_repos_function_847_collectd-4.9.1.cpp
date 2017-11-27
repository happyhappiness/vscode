static int submit_volume_perf_data (const char *hostname, /* {{{ */
		data_volume_perf_t *old_data,
		const data_volume_perf_t *new_data)
{
	char plugin_instance[DATA_MAX_NAME_LEN];

	if ((hostname == NULL) || (old_data == NULL) || (new_data == NULL))
		return (-1);

	ssnprintf (plugin_instance, sizeof (plugin_instance),
			"volume-%s", old_data->name);

	/* Check for and submit disk-octet values */
	if (HAS_ALL_FLAGS (old_data->flags, CFG_VOLUME_PERF_IO)
			&& HAS_ALL_FLAGS (new_data->flags, HAVE_VOLUME_PERF_BYTES_READ | HAVE_VOLUME_PERF_BYTES_WRITE))
	{
		submit_two_counters (hostname, plugin_instance, "disk_octets", /* type instance = */ NULL,
				(counter_t) new_data->read_bytes, (counter_t) new_data->write_bytes, new_data->timestamp);
	}

	/* Check for and submit disk-operations values */
	if (HAS_ALL_FLAGS (old_data->flags, CFG_VOLUME_PERF_OPS)
			&& HAS_ALL_FLAGS (new_data->flags, HAVE_VOLUME_PERF_OPS_READ | HAVE_VOLUME_PERF_OPS_WRITE))
	{
		submit_two_counters (hostname, plugin_instance, "disk_ops", /* type instance = */ NULL,
				(counter_t) new_data->read_ops, (counter_t) new_data->write_ops, new_data->timestamp);
	}

	/* Check for, calculate and submit disk-latency values */
	if (HAS_ALL_FLAGS (old_data->flags, CFG_VOLUME_PERF_LATENCY
				| HAVE_VOLUME_PERF_OPS_READ | HAVE_VOLUME_PERF_OPS_WRITE
				| HAVE_VOLUME_PERF_LATENCY_READ | HAVE_VOLUME_PERF_LATENCY_WRITE)
			&& HAS_ALL_FLAGS (new_data->flags, HAVE_VOLUME_PERF_OPS_READ | HAVE_VOLUME_PERF_OPS_WRITE
				| HAVE_VOLUME_PERF_LATENCY_READ | HAVE_VOLUME_PERF_LATENCY_WRITE))
	{
		gauge_t latency_per_op_read;
		gauge_t latency_per_op_write;

		latency_per_op_read = NAN;
		latency_per_op_write = NAN;

		/* Check if a counter wrapped around. */
		if ((new_data->read_ops > old_data->read_ops)
				&& (new_data->read_latency > old_data->read_latency))
		{
			uint64_t diff_ops_read;
			uint64_t diff_latency_read;

			diff_ops_read = new_data->read_ops - old_data->read_ops;
			diff_latency_read = new_data->read_latency - old_data->read_latency;

			if (diff_ops_read > 0)
				latency_per_op_read = ((gauge_t) diff_latency_read) / ((gauge_t) diff_ops_read);
		}

		if ((new_data->write_ops > old_data->write_ops)
				&& (new_data->write_latency > old_data->write_latency))
		{
			uint64_t diff_ops_write;
			uint64_t diff_latency_write;

			diff_ops_write = new_data->write_ops - old_data->write_ops;
			diff_latency_write = new_data->write_latency - old_data->write_latency;

			if (diff_ops_write > 0)
				latency_per_op_write = ((gauge_t) diff_latency_write) / ((gauge_t) diff_ops_write);
		}

		submit_two_gauge (hostname, plugin_instance, "disk_latency", /* type instance = */ NULL,
				latency_per_op_read, latency_per_op_write, new_data->timestamp);
	}

	/* Clear all HAVE_* flags. */
	old_data->flags &= ~HAVE_VOLUME_PERF_ALL;

	/* Copy all counters */
	old_data->timestamp = new_data->timestamp;
	old_data->read_bytes = new_data->read_bytes;
	old_data->write_bytes = new_data->write_bytes;
	old_data->read_ops = new_data->read_ops;
	old_data->write_ops = new_data->write_ops;
	old_data->read_latency = new_data->read_latency;
	old_data->write_latency = new_data->write_latency;

	/* Copy the HAVE_* flags */
	old_data->flags |= (new_data->flags & HAVE_VOLUME_PERF_ALL);

	return (0);
}