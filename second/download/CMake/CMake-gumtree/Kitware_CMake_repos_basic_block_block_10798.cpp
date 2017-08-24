{
					if ((p = header_bytes(a, 4)) == NULL)
						return (-1);
					entries[i].attr = archive_le32dec(p);
				}