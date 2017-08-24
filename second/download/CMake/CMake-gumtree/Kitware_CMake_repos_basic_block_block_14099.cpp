{
		const char *ucptr;
		uint32_t cp1, cp2;
		int SIndex;
		struct {
			uint32_t uc;
			int ccc;
		} fdc[FDC_MAX];
		int fdi, fdj;
		int ccc;

check_first_code:
		if (n < 0) {
			/* Use a replaced unicode character. */
			UNPARSE(p, endp, uc);
			s += n*-1;
			len -= n*-1;
			ret = -1;
			continue;
		} else if (n == spair || always_replace)
			/* uc is converted from a surrogate pair.
			 * this should be treated as a changed code. */
			ucptr = NULL;
		else
			ucptr = s;
		s += n;
		len -= n;

		/* Hangul Decomposition. */
		if ((SIndex = uc - HC_SBASE) >= 0 && SIndex < HC_SCOUNT) {
			int L = HC_LBASE + SIndex / HC_NCOUNT;
			int V = HC_VBASE + (SIndex % HC_NCOUNT) / HC_TCOUNT;
			int T = HC_TBASE + SIndex % HC_TCOUNT;

			REPLACE_UC_WITH(L);
			WRITE_UC();
			REPLACE_UC_WITH(V);
			WRITE_UC();
			if (T != HC_TBASE) {
				REPLACE_UC_WITH(T);
				WRITE_UC();
			}
			continue;
		}
		if (IS_DECOMPOSABLE_BLOCK(uc) && CCC(uc) != 0) {
			WRITE_UC();
			continue;
		}

		fdi = 0;
		while (get_nfd(&cp1, &cp2, uc) && fdi < FDC_MAX) {
			int k;

			for (k = fdi; k > 0; k--)
				fdc[k] = fdc[k-1];
			fdc[0].ccc = CCC(cp2);
			fdc[0].uc = cp2;
			fdi++;
			REPLACE_UC_WITH(cp1);
		}

		/* Read following code points. */
		while ((n2 = parse(&uc2, s, len)) > 0 &&
		    (ccc = CCC(uc2)) != 0 && fdi < FDC_MAX) {
			int j, k;

			s += n2;
			len -= n2;
			for (j = 0; j < fdi; j++) {
				if (fdc[j].ccc > ccc)
					break;
			}
			if (j < fdi) {
				for (k = fdi; k > j; k--)
					fdc[k] = fdc[k-1];
				fdc[j].ccc = ccc;
				fdc[j].uc = uc2;
			} else {
				fdc[fdi].ccc = ccc;
				fdc[fdi].uc = uc2;
			}
			fdi++;
		}

		WRITE_UC();
		for (fdj = 0; fdj < fdi; fdj++) {
			REPLACE_UC_WITH(fdc[fdj].uc);
			WRITE_UC();
		}

		if (n2 == 0)
			break;
		REPLACE_UC_WITH(uc2);
		n = n2;
		goto check_first_code;
	}