int http_get_info_packs(const char *base_url, struct packed_git **packs_head)
{
	struct http_get_options options = {0};
	int ret = 0, i = 0;
	char *url, *data;
	struct strbuf buf = STRBUF_INIT;
	unsigned char sha1[20];

	end_url_with_slash(&buf, base_url);
	strbuf_addstr(&buf, "objects/info/packs");
	url = strbuf_detach(&buf, NULL);

	options.no_cache = 1;
	ret = http_get_strbuf(url, &buf, &options);
	if (ret != HTTP_OK)
		goto cleanup;

	data = buf.buf;
	while (i < buf.len) {
		switch (data[i]) {
		case 'P':
			i++;
			if (i + 52 <= buf.len &&
			    starts_with(data + i, " pack-") &&
			    starts_with(data + i + 46, ".pack\n")) {
				get_sha1_hex(data + i + 6, sha1);
				fetch_and_setup_pack_index(packs_head, sha1,
						      base_url);
				i += 51;
				break;
			}
		default:
			while (i < buf.len && data[i] != '\n')
				i++;
		}
		i++;
	}

cleanup:
	free(url);
	return ret;
}