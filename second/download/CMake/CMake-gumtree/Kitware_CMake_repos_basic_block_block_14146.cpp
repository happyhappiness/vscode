{
				uint16_t v = archive_le16dec(u16);
				archive_be16enc(u16, v);
				u16 += 2;
				count--;
			}