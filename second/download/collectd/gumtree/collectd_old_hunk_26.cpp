		if (instance != NULL) free (instance); instance = NULL;
		if (values   != NULL) free (values);   values   = NULL;
	}
	
	return (0);
}

int main (int argc, char **argv)
{
	struct sigaction sigIntAction, sigChldAction;
	pid_t pid;

	char *plugindir = NULL;
	char *basedir = "/var/lib/collectd";

	operating_mode = MODE_LOCAL;
	
	/*
	 * open syslog
	 */
	openlog (PACKAGE, LOG_CONS | LOG_PID, LOG_DAEMON);

