(!CryptAcquireContext(&ctx->cryptProv, NULL, NULL,
		    PROV_RSA_FULL, CRYPT_NEWKEYSET))
			return (ARCHIVE_FAILED);