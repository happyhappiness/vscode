{
			if (mb) {
				/* This may be second byte of multi-byte
				 * character. */
				break;
			}
			fn->s[i] = '/';
			mb = 0;
		}