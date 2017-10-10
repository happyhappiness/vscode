		write_or_die(out, req_buf.buf, req_buf.len);
		packet_flush(out);
	}
	strbuf_release(&req_buf);
	strbuf_release(&cap_buf);

	if (use_push_options) {
		struct string_list_item *item;
		struct strbuf sb = STRBUF_INIT;

		for_each_string_list_item(item, args->push_options)
			packet_buf_write(&sb, "%s", item->string);

		write_or_die(out, sb.buf, sb.len);
		packet_flush(out);
		strbuf_release(&sb);
	}

	if (use_sideband && cmds_sent) {
		memset(&demux, 0, sizeof(demux));
		demux.proc = sideband_demux;
		demux.data = fd;
		demux.out = -1;
		demux.isolate_sigpipe = 1;
