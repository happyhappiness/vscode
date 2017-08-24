(strcmp(tc, "CP932") == 0)
				sc->cd = iconv_open("SJIS", fc);
			else if (strcmp(fc, "CP932") == 0)
				sc->cd = iconv_open(tc, "SJIS")