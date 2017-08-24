{
		unsigned char flag = *data++;
		unsigned char nlen = *data++;
		data_length -= 2;

		archive_strcat(&file->symlink, separator);
		separator = "/";

		switch(flag) {
		case 0: /* Usual case, this is text. */
			if (data_length < nlen)
				return;
			archive_strncat(&file->symlink,
			    (const char *)data, nlen);
			break;
		case 0x01: /* Text continues in next component. */
			if (data_length < nlen)
				return;
			archive_strncat(&file->symlink,
			    (const char *)data, nlen);
			separator = "";
			break;
		case 0x02: /* Current dir. */
			archive_strcat(&file->symlink, ".");
			break;
		case 0x04: /* Parent dir. */
			archive_strcat(&file->symlink, "..");
			break;
		case 0x08: /* Root of filesystem. */
			archive_strcat(&file->symlink, "/");
			separator = "";
			break;
		case 0x10: /* Undefined (historically "volume root" */
			archive_string_empty(&file->symlink);
			archive_strcat(&file->symlink, "ROOT");
			break;
		case 0x20: /* Undefined (historically "hostname") */
			archive_strcat(&file->symlink, "hostname");
			break;
		default:
			/* TODO: issue a warning ? */
			return;
		}
		data += nlen;
		data_length -= nlen;
	}