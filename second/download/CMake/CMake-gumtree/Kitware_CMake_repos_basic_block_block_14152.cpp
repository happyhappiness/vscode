{
		count = MultiByteToWideChar(sc->from_cp,
		    MB_PRECOMPOSED, s, (int)length, (LPWSTR)u16, (int)avail>>1);
		/* Exit loop if we succeeded */
		if (count != 0 ||
		    GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
			break;
		}
		/* Expand buffer and try again */
		count = MultiByteToWideChar(sc->from_cp,
		    MB_PRECOMPOSED, s, (int)length, NULL, 0);
		if (archive_string_ensure(as16, (count +1) * 2)
		    == NULL)
			return (-1);
		u16 = as16->s + as16->length;
		avail = as16->buffer_length - 2;
	}