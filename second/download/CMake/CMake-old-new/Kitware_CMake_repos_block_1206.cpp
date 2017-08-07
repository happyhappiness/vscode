{
				unsigned algId =
					archive_le16dec(p + offset + 2);
				unsigned bitLen =
					archive_le16dec(p + offset + 4);
				int	 flags =
					archive_le16dec(p + offset + 6);
				fprintf(stderr, "algId=0x%04x, bitLen=%u, "
				    "flgas=%d\n", algId, bitLen,flags);
			}