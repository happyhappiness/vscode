(archive_le16dec(zip->file_header + 6) < 45)
			archive_le16enc(zip->file_header + 6, 45)