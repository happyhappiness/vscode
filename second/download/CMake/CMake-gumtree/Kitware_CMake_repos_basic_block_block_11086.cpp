(fn->s[i] == '\\') {
			if (mb) {
				/* This may be second byte of multi-byte
				 * character. */
				break;
			}
			fn->s[i] = '/';
			mb = 0;
		} else if ((fn->s[i] & 0x80) && !(attr & ATTR_NAME_IS_UTF))
			mb = 1;
		else
			mb = 0