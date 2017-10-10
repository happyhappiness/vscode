		if (checkout_target(&the_index, ce, &st))
			return -1;
	}
	if (verify_index_match(ce, &st))
		return error(_("%s: does not match index"), name);

	status = load_patch_target(&buf, ce, &st, name, mode);
	if (status < 0)
		return status;
	else if (status)
		return -1;
	img = strbuf_detach(&buf, &len);
	prepare_image(image, img, len, !patch->is_binary);
	return 0;
}

static int try_threeway(struct image *image, struct patch *patch,
			struct stat *st, const struct cache_entry *ce)
{
	unsigned char pre_sha1[20], post_sha1[20], our_sha1[20];
	struct strbuf buf = STRBUF_INIT;
	size_t len;
	int status;
	char *img;
