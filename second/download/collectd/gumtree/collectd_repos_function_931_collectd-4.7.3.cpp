static void log_status (int status)
{
	if (WIFEXITED (status)) {
		if (0 == WEXITSTATUS (status))
			syslog (LOG_INFO, "Info: collectd terminated with exit status %i",
					WEXITSTATUS (status));
		else
			syslog (LOG_WARNING,
					"Warning: collectd terminated with exit status %i",
					WEXITSTATUS (status));
	}
	else if (WIFSIGNALED (status)) {
		syslog (LOG_WARNING, "Warning: collectd was terminated by signal %i%s",
				WTERMSIG (status), WCOREDUMP (status) ? " (core dumped)" : "");
	}
	return;
}