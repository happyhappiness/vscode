{
			if (!joliet_allowed_char(p[0], p[1]))
				archive_be16enc(p, 0x005F); /* '_' */
			else if (p[0] == 0 && p[1] == 0x2E) /* '.' */
				dot = p;
			p += 2;
			lt -= 2;
		}