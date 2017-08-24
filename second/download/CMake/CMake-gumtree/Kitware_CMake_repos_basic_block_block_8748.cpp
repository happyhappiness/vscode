(keyObj == NULL) {
		BCryptCloseAlgorithmProvider(hAlg, 0);
		return -1;
	}