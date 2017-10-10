		} else {
			packet_buf_write(&req_buf, "%s %s %s",
					 old_hex, new_hex, ref->name);
		}
	}

	if (use_push_options) {
		struct string_list_item *item;

		packet_buf_flush(&req_buf);
		for_each_string_list_item(item, args->push_options)
			packet_buf_write(&req_buf, "%s", item->string);
	}

	if (args->stateless_rpc) {
		if (!args->dry_run && (cmds_sent || is_repository_shallow())) {
			packet_buf_flush(&req_buf);
			send_sideband(out, -1, req_buf.buf, req_buf.len, LARGE_PACKET_MAX);
		}
	} else {
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
