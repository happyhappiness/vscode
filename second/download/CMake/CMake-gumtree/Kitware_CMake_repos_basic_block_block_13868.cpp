(sc->cd_w == (iconv_t)-1 &&
			    (sc->flag & SCONV_BEST_EFFORT)) {
				if (strcmp(fc, "CP932") == 0)
					sc->cd_w = iconv_open("UTF-8", "SJIS");
			}