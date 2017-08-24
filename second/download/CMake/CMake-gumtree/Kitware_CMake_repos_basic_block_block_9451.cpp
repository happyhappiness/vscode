(a->flags & ARCHIVE_READDISK_MAC_COPYFILE) {
		r1 = setup_mac_metadata(a, entry, &fd);
		if (r1 < r)
			r = r1;
	}