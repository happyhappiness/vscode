(is_big_endian()) {
		if (!bigendian) {
			while (count > 0) {
				uint16_t v = archive_be16dec(u16);
				archive_le16enc(u16, v);
				u16 += 2;
				count--;
			}
		}
	} else {
		if (bigendian) {
			while (count > 0) {
				uint16_t v = archive_le16dec(u16);
				archive_be16enc(u16, v);
				u16 += 2;
				count--;
			}
		}
	}