	else
		ret = 0;
	if (args->stateless_rpc)
		packet_flush(out);

	if (use_sideband && cmds_sent) {
		if (finish_async(&demux)) {
			error("error in sideband demultiplexer");
			ret = -1;
		}
		close(demux.out);
	}

	if (ret < 0)
		return ret;

	if (args->porcelain)
