{
			uint16_t *u16 = (uint16_t *)(dest->s + dest->length);
			int b;
			for (b = 0; b < count; b++) {
				uint16_t val = archive_le16dec(u16+b);
				archive_be16enc(u16+b, val);
			}
		}