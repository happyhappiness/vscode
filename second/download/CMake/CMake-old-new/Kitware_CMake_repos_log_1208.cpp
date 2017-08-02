fprintf(stderr, "uid %d gid %d\n",
			    archive_le16dec(p + offset),
			    archive_le16dec(p + offset + 2))