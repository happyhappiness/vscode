{
		unsigned uc2;

		if (n >= 4) {
			if (be)
				uc2 = archive_be16dec(utf16);
			else
				uc2 = archive_le16dec(utf16);
		} else
			uc2 = 0;
		if (IS_LOW_SURROGATE_LA(uc2)) {
			uc = combine_surrogate_pair(uc, uc2);
			utf16 += 2;
		} else {
	 		/* Undescribed code point should be U+FFFD
		 	* (replacement character). */
			*pwc = UNICODE_R_CHAR;
			return (-2);
		}
	}