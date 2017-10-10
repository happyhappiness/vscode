		 */
		demux.proc = sideband_demux;
		demux.data = xd;
		demux.out = -1;
		demux.isolate_sigpipe = 1;
		if (start_async(&demux))
			die("fetch-pack: unable to fork off sideband"
			    " demultiplexer");
	}
	else
		demux.out = xd[0];

	if (!args->keep_pack && unpack_limit) {

		if (read_pack_header(demux.out, &header))
			die("protocol error: bad pack header");
		pass_header = 1;
		if (ntohl(header.hdr_entries) < unpack_limit)
			do_keep = 0;
		else
			do_keep = 1;
	}
