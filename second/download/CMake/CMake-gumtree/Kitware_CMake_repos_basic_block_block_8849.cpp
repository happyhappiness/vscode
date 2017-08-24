{
		BCryptCloseAlgorithmProvider(hAlg, 0);
		HeapFree(GetProcessHeap(), 0, hash);
		return -1;
	}