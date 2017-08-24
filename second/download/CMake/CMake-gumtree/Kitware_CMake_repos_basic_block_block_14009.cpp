(cnt == 3 && IS_LOW_SURROGATE_LA(wc)) {
		/* Invalid byte sequence. */
		goto invalid_sequence;
	}