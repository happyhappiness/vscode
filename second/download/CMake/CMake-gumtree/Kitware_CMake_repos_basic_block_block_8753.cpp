{
		BCryptCloseAlgorithmProvider(ctx->hAlg, 0);
		ctx->hAlg = NULL;
		BCryptDestroyKey(ctx->hKey);
		ctx->hKey = NULL;
		HeapFree(GetProcessHeap(), 0, ctx->keyObj);
		ctx->keyObj = NULL;
	}