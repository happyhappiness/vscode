
	if (use_sideband && cmds_sent) {
		memset(&demux, 0, sizeof(demux));
		demux.proc = sideband_demux;
		demux.data = fd;
		demux.out = -1;
		demux.isolate_sigpipe = 1;
		if (start_async(&demux))
			die("send-pack: unable to fork off sideband demultiplexer");
		in = demux.out;
	}

	if (need_pack_data && cmds_sent) {
