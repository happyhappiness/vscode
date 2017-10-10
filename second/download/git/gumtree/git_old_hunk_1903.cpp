		}
	} else {
		write_or_die(out, req_buf.buf, req_buf.len);
		packet_flush(out);
	}
	strbuf_release(&req_buf);

	if (use_sideband && cmds_sent) {
		memset(&demux, 0, sizeof(demux));
		demux.proc = sideband_demux;
		demux.data = fd;
		demux.out = -1;
		if (start_async(&demux))
			die("send-pack: unable to fork off sideband demultiplexer");
		in = demux.out;
	}

	if (new_refs && cmds_sent) {
		if (pack_objects(out, remote_refs, extra_have, args) < 0) {
			for (ref = remote_refs; ref; ref = ref->next)
				ref->status = REF_STATUS_NONE;
			if (args->stateless_rpc)
				close(out);
			if (git_connection_is_socket(conn))
