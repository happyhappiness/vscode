static void http_config(void)
{
	int i, value = 0;
	struct strbuf var = STRBUF_INIT;

	git_config_get_bool("http.getanyfile", &getanyfile);
	git_config_get_ulong("http.maxrequestbuffer", &max_request_buffer);

	for (i = 0; i < ARRAY_SIZE(rpc_service); i++) {
		struct rpc_service *svc = &rpc_service[i];
		strbuf_addf(&var, "http.%s", svc->config_name);
		if (!git_config_get_bool(var.buf, &value))
			svc->enabled = value;
		strbuf_reset(&var);
	}

	strbuf_release(&var);
}