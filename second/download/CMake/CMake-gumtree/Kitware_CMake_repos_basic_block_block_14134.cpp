{
				uint16_t val = archive_le16dec(tmp.s+b);
				archive_be16enc(tmp.s+b, val);
			}