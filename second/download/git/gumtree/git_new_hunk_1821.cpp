			die("fetch-pack: unable to fork off sideband"
			    " demultiplexer");
	}
	else
		demux.out = xd[0];

	cmd.argv = argv;
	av = argv;
	*hdr_arg = 0;
	if (!args->keep_pack && unpack_limit) {
		struct pack_header header;

