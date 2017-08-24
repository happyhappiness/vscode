(!BCRYPT_SUCCESS(status)) {
		BCryptCloseAlgorithmProvider(hAlg, 0);
		HeapFree(GetProcessHeap(), 0, keyObj);
		return -1;
	}