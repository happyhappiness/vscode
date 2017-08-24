{
		BCryptCloseAlgorithmProvider(ctx->hAlg, 0);
		HeapFree(GetProcessHeap(), 0, ctx->hash);
		ctx->hAlg = NULL;
	}