(strcmp(value, "lzma1") == 0 ||
		    strcmp(value, "LZMA1") == 0)
#if HAVE_LZMA_H
			zip->opt_compression = _7Z_LZMA1