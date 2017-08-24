{
		if (*len + file->utf16be_bytes > max)
			return (-1);/* Path is too long! */
		memcpy(p + *len, file->utf16be_name, file->utf16be_bytes);
		*len += file->utf16be_bytes;
	}