(key_lengths.dwMinLength > aes_key_len
		|| key_lengths.dwMaxLength < aes_key_len) {
		BCryptCloseAlgorithmProvider(hAlg, 0);
		return -1;
	}