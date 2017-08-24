(strcmp(fc, "CP932") == 0)
					sc->cd_w = iconv_open("UTF-8", "SJIS")