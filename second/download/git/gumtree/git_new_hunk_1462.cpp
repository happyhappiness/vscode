
	strbuf_addf(&buf, "%s.temp", sha1_pack_index_name(sha1));
	tmp = strbuf_detach(&buf, NULL);

	if (http_get_file(url, tmp, NULL) != HTTP_OK) {
		error("Unable to get pack index %s", url);
		FREE_AND_NULL(tmp);
	}

	free(url);
	return tmp;
}

