
	for (i = 0; i < nr_heads; i++) {
		struct ref *ref = to_fetch[i];
		if (!*ref->name)
			die("cannot fetch by sha1 over smart http");
		packet_buf_write(&preamble, "%s %s\n",
				 oid_to_hex(&ref->old_oid), ref->name);
	}
	packet_buf_flush(&preamble);

	memset(&rpc, 0, sizeof(rpc));
	rpc.service_name = "git-upload-pack",
	rpc.argv = argv;
