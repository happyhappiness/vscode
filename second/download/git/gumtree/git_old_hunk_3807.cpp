		write_or_die(out, req_buf.buf, req_buf.len);
		packet_flush(out);
	}
	strbuf_release(&req_buf);
	strbuf_release(&cap_buf);

	if (use_sideband && cmds_sent) {
		memset(&demux, 0, sizeof(demux));
		demux.proc = sideband_demux;
		demux.data = fd;
		demux.out = -1;
		demux.isolate_sigpipe = 1;
