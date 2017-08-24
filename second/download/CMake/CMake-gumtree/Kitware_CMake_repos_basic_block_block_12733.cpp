{
		int err2 = read_mac_metadata_blob(a, tar, entry, h, unconsumed);
		if (err2 < err)
			err = err2;
	}