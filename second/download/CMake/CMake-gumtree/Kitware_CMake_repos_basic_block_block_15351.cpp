(strcmp(value, "lzma2") == 0 ||
		    strcmp(value, "LZMA2") == 0)
#if HAVE_LZMA_H
			zip->opt_compression = _7Z_LZMA2