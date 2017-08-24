{
				uint16_t val = archive_be16dec(u16+b);
				archive_le16enc(u16+b, val);
			}