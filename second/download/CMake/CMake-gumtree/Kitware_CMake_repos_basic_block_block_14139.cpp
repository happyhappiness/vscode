{
		defchar = 0;
		ll = WideCharToMultiByte(sc->to_cp, 0,
		    (LPCWSTR)u16, (int)bytes>>1, mbs, (int)mbs_size,
			NULL, &defchar);
		/* Exit loop if we succeeded */
		if (ll != 0 ||
		    GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
			break;
		}
		/* Else expand buffer and loop to try again. */
		ll = WideCharToMultiByte(sc->to_cp, 0,
		    (LPCWSTR)u16, (int)bytes, NULL, 0, NULL, NULL);
		if (archive_string_ensure(as, ll +1) == NULL)
			return (-1);
		mbs = as->s + as->length;
		mbs_size = as->buffer_length - as->length -1;
	}