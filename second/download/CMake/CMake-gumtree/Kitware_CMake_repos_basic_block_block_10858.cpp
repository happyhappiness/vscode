(*p) {
		if (parse_7zip_uint64(a, &(h->dataIndex)) < 0)
			goto failed;
		if (UMAX_ENTRY < h->dataIndex)
			goto failed;
	}