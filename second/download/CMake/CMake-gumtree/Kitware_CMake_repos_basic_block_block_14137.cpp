(b = 0; b < bytes; b += 2) {
				uint16_t val = archive_be16dec(tmp.s+b);
				archive_le16enc(tmp.s+b, val);
			}