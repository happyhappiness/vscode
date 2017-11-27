static int zookeeper_config(const char *key, const char *value)
{
	if (strncmp(key, "Host", strlen("Host")) == 0)
	{
		sfree (zk_host);
		zk_host = strdup (value);
	}
	else if (strncmp(key, "Port", strlen("Port")) == 0)
	{
		sfree (zk_port);
		zk_port = strdup (value);
	}
	else
	{
		return -1;
	}
	return 0;
}