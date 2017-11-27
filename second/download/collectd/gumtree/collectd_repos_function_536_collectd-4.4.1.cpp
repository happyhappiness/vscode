static void *dns_child_loop (void *dummy)
{
	pcap_t *pcap_obj;
	char    pcap_error[PCAP_ERRBUF_SIZE];
	struct  bpf_program fp;

	int status;

	/* Don't block any signals */
	{
		sigset_t sigmask;
		sigemptyset (&sigmask);
		pthread_sigmask (SIG_SETMASK, &sigmask, NULL);
	}

	/* Passing `pcap_device == NULL' is okay and the same as passign "any" */
	DEBUG ("Creating PCAP object..");
	pcap_obj = pcap_open_live (pcap_device,
			PCAP_SNAPLEN,
			0 /* Not promiscuous */,
			interval_g,
			pcap_error);
	if (pcap_obj == NULL)
	{
		ERROR ("dns plugin: Opening interface `%s' "
				"failed: %s",
				(pcap_device != NULL) ? pcap_device : "any",
				pcap_error);
		return (NULL);
	}

	memset (&fp, 0, sizeof (fp));
	if (pcap_compile (pcap_obj, &fp, "udp port 53", 1, 0) < 0)
	{
		ERROR ("dns plugin: pcap_compile failed");
		return (NULL);
	}
	if (pcap_setfilter (pcap_obj, &fp) < 0)
	{
		ERROR ("dns plugin: pcap_setfilter failed");
		return (NULL);
	}

	DEBUG ("PCAP object created.");

	dnstop_set_pcap_obj (pcap_obj);
	dnstop_set_callback (dns_child_callback);

	status = pcap_loop (pcap_obj,
			-1 /* loop forever */,
			handle_pcap /* callback */,
			NULL /* Whatever this means.. */);
	if (status < 0)
		ERROR ("dns plugin: Listener thread is exiting "
				"abnormally: %s", pcap_geterr (pcap_obj));

	DEBUG ("child is exiting");

	pcap_close (pcap_obj);
	listen_thread_init = 0;
	pthread_exit (NULL);

	return (NULL);
}