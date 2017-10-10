		end_headers();

		packet_write(1, "# service=git-%s\n", svc->name);
		packet_flush(1);

		argv[0] = svc->name;
		run_service(argv);

	} else {
		select_getanyfile();
		for_each_namespaced_ref(show_text_ref, &buf);
		send_strbuf("text/plain", &buf);
	}
