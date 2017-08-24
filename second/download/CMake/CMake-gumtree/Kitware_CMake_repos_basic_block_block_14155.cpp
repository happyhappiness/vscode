{
			if (bigendian)
				archive_be16enc(u16, *s);
			else
				archive_le16enc(u16, *s);
			u16 += 2;
			s++;
			count++;
		}