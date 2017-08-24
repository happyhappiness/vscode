{
		if (remaining < 2)
			return (0);
		archive_le16enc(utf16, uc);
		return (2);
	}