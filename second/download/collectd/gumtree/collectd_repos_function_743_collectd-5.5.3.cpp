static int pf_read (void)
{
	struct pf_status state;
	int fd;
	int status;
	int i;

	fd = open (pf_device, O_RDONLY);
	if (fd < 0)
	{
		char errbuf[1024];
		ERROR("pf plugin: Unable to open %s: %s",
				pf_device,
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return (-1);
	}

	memset (&state, 0, sizeof (state));
	status = ioctl (fd, DIOCGETSTATUS, &state);
	if (status != 0)
	{
		char errbuf[1024];
		ERROR("pf plugin: ioctl(DIOCGETSTATUS) failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		close(fd);
		return (-1);
	}

	close (fd);
	fd = -1;

	if (!state.running)
	{
		WARNING ("pf plugin: PF is not running.");
		return (-1);
	}

	for (i = 0; i < PFRES_MAX; i++)
		pf_submit ("pf_counters", pf_reasons[i], state.counters[i],
				/* is gauge = */ 0);
	for (i = 0; i < LCNT_MAX; i++)
		pf_submit ("pf_limits", pf_lcounters[i], state.lcounters[i],
				/* is gauge = */ 0);
	for (i = 0; i < FCNT_MAX; i++)
		pf_submit ("pf_state", pf_fcounters[i], state.fcounters[i],
				/* is gauge = */ 0);
	for (i = 0; i < SCNT_MAX; i++)
		pf_submit ("pf_source", pf_scounters[i], state.scounters[i],
				/* is gauge = */ 0);

	pf_submit ("pf_states", "current", (uint32_t) state.states,
			/* is gauge = */ 1);

	return (0);
}