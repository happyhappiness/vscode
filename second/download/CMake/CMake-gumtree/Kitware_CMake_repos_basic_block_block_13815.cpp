(count < (int)len && *ws) {
				archive_be16enc(u16+count, *ws);
				ws++;
				count++;
			}