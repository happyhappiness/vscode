
		strbuf_addf(&buf, "application/x-git-%s-advertisement",
			svc->name);
		hdr_str(hdr, content_type, buf.buf);
		end_headers(hdr);

		packet_write(1, "# service=git-%s\n", svc->name);
		packet_flush(1);

		argv[0] = svc->name;
		run_service(argv, 0);

	} else {
