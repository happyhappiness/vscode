{
			if (archive_string_ensure(&tmp, bytes+2) == NULL)
				return (-1);
			memcpy(tmp.s, _p, bytes);
			for (b = 0; b < bytes; b += 2) {
				uint16_t val = archive_le16dec(tmp.s+b);
				archive_be16enc(tmp.s+b, val);
			}
			u16 = tmp.s;
		}