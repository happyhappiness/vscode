(strcmp(fc, "CP932") == 0)
				sc->cd = iconv_open(tc, "SJIS")