		if (checkout_target(&the_index, ce, &st))
			return -1;
	}
	if (verify_index_match(ce, &st))
		return error(_("%s: does not match index"), name);

	status = load_patch_target(state, &buf, ce, &st, name, mode);
	if (status < 0)
		return status;
	else if (status)
		return -1;
	img = strbuf_detach(&buf, &len);
	prepare_image(image, img, len, !patch->is_binary);
