				error("invalid key (newline): %s", key);
			goto out_free_ret_1;
		}
		if (store_key)
			(*store_key)[i] = c;
	}

	return 0;

out_free_ret_1:
	if (store_key) {
		free(*store_key);
