static void service_rpc(struct strbuf *hdr, char *service_name)
{
	const char *argv[] = {NULL, "--stateless-rpc", ".", NULL};
	struct rpc_service *svc = select_service(hdr, service_name);
	struct strbuf buf = STRBUF_INIT;

	strbuf_reset(&buf);
	strbuf_addf(&buf, "application/x-git-%s-request", svc->name);
	check_content_type(hdr, buf.buf);

	hdr_nocache(hdr);

	strbuf_reset(&buf);
	strbuf_addf(&buf, "application/x-git-%s-result", svc->name);
	hdr_str(hdr, content_type, buf.buf);

	end_headers(hdr);

	argv[0] = svc->name;
	run_service(argv, svc->buffer_input);
	strbuf_release(&buf);
}