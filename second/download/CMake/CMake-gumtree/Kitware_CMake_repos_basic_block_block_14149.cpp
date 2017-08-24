(count > 0) {
				uint16_t v = archive_be16dec(u16);
				archive_le16enc(u16, v);
				u16 += 2;
				count--;
			}