
		if (!delta_data) {
			error("failed to unpack compressed delta "
			      "at offset %"PRIuMAX" from %s",
			      (uintmax_t)curpos, p->pack_name);
			data = NULL;
			free(external_base);
			continue;
		}

		data = patch_delta(base, base_size,
				   delta_data, delta_size,
				   &size);
