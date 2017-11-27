static int zookeeper_read (void) {
	char buf[4096];
	char *ptr;
	char *save_ptr;
	char *line;
	char *fields[2];

	if (zookeeper_query (buf, sizeof (buf)) < 0)
	{
		return (-1);
	}

	ptr = buf;
	save_ptr = NULL;
	while ((line = strtok_r (ptr, "\n\r", &save_ptr)) != NULL)
	{
		ptr = NULL;
		if (strsplit(line, fields, 2) != 2)
		{
			continue;
		}
#define FIELD_CHECK(check, expected) \
	(strncmp (check, expected, strlen(expected)) == 0)

		if (FIELD_CHECK (fields[0], "zk_avg_latency"))
		{
			zookeeper_submit_gauge ("latency", "avg", atol(fields[1]));
		}
		else if (FIELD_CHECK(fields[0], "zk_min_latency"))
		{
			zookeeper_submit_gauge ("latency", "min", atol(fields[1]));
		}
		else if (FIELD_CHECK (fields[0], "zk_max_latency"))
		{
			zookeeper_submit_gauge ("latency", "max", atol(fields[1]));
		}
		else if (FIELD_CHECK (fields[0], "zk_packets_received"))
		{
			zookeeper_submit_derive ("packets", "received", atol(fields[1]));
		}
		else if (FIELD_CHECK (fields[0], "zk_packets_sent"))
		{
			zookeeper_submit_derive ("packets", "sent", atol(fields[1]));
		}
		else if (FIELD_CHECK (fields[0], "zk_num_alive_connections"))
		{
			zookeeper_submit_gauge ("current_connections", NULL, atol(fields[1]));
		}
		else if (FIELD_CHECK (fields[0], "zk_outstanding_requests"))
		{
			zookeeper_submit_gauge ("requests", "outstanding", atol(fields[1]));
		}
		else if (FIELD_CHECK (fields[0], "zk_znode_count"))
		{
			zookeeper_submit_gauge ("gauge", "znode", atol(fields[1]));
		}
		else if (FIELD_CHECK (fields[0], "zk_watch_count"))
		{
			zookeeper_submit_gauge ("gauge", "watch", atol(fields[1]));
		}
		else if (FIELD_CHECK (fields[0], "zk_ephemerals_count"))
		{
			zookeeper_submit_gauge ("gauge", "ephemerals", atol(fields[1]));
		}
		else if (FIELD_CHECK (fields[0], "zk_ephemerals_count"))
		{
			zookeeper_submit_gauge ("gauge", "ephemerals", atol(fields[1]));
		}
		else if (FIELD_CHECK (fields[0], "zk_ephemerals_count"))
		{
			zookeeper_submit_gauge ("gauge", "ephemerals", atol(fields[1]));
		}
		else if (FIELD_CHECK (fields[0], "zk_approximate_data_size"))
		{
			zookeeper_submit_gauge ("bytes", "approximate_data_size", atol(fields[1]));
		}
		else if (FIELD_CHECK (fields[0], "zk_followers"))
		{
			zookeeper_submit_gauge ("count", "followers", atol(fields[1]));
		}
		else if (FIELD_CHECK (fields[0], "zk_synced_followers"))
		{
			zookeeper_submit_gauge ("count", "synced_followers", atol(fields[1]));
		}
		else if (FIELD_CHECK (fields[0], "zk_pending_syncs"))
		{
			zookeeper_submit_gauge ("count", "pending_syncs", atol(fields[1]));
		}
		else
		{
			DEBUG("Uncollected zookeeper MNTR field %s", fields[0]);
		}
	}

	return (0);
}