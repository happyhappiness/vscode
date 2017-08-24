{
				uint16_t val = archive_le16dec(u16+b);
				archive_be16enc(u16+b, val);
			}