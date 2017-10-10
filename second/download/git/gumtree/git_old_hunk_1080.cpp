
	curl_slist_free_all(headers);
	strbuf_release(&buf);
	return err;
}

static int post_rpc(struct rpc_state *rpc)
{
	struct active_request_slot *slot;
	struct curl_slist *headers = http_copy_default_headers();
	int use_gzip = rpc->gzip_request;
	char *gzip_body = NULL;
