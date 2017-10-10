
	curl_slist_free_all(headers);
	strbuf_release(&buf);
	return err;
}

static curl_off_t xcurl_off_t(ssize_t len) {
	if (len > maximum_signed_value_of_type(curl_off_t))
		die("cannot handle pushes this big");
	return (curl_off_t) len;
}

static int post_rpc(struct rpc_state *rpc)
{
	struct active_request_slot *slot;
	struct curl_slist *headers = http_copy_default_headers();
	int use_gzip = rpc->gzip_request;
	char *gzip_body = NULL;
