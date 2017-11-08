static void get_info_refs(struct strbuf *hdr, char *arg)
{
	const char *service_name = get_parameter("service");
	struct strbuf buf = STRBUF_INIT;

	hdr_nocache(hdr);

	if (service_name) {
		const char *argv[] = {NULL /* service name */,
			"--stateless-rpc", "--advertise-refs",
			".", NULL};
		struct rpc_service *svc = select_service(hdr, service_name);

		strbuf_addf(&buf, "application/x-git-%s-advertisement",
			svc->name);
		hdr_str(hdr, content_type, buf.buf);
		end_headers(hdr);

		packet_write(1, "# service=git-%s\n", svc->name);
		packet_flush(1);

		argv[0] = svc->name;
		run_service(argv, 0);

	} else {
		select_getanyfile(hdr);
		for_each_namespaced_ref(show_text_ref, &buf);
		send_strbuf(hdr, "text/plain", &buf);
	}
	strbuf_release(&buf);
}