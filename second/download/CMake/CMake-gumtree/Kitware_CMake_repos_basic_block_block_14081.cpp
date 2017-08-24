{
		const char *ucptr, *uc2ptr;

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

		/* Read second code point. */
		while ((n2 = parse(&uc2, s, len)) > 0) {
			uint32_t ucx[FDC_MAX];
			int ccx[FDC_MAX];
			int cl, cx, i, nx, ucx_size;
			int LIndex,SIndex;
			uint32_t nfc;

			if (n2 == spair || always_replace)
				/* uc2 is converted from a surrogate pair.
			 	 * this should be treated as a changed code. */
				uc2ptr = NULL;
			else
				uc2ptr = s;
			s += n2;
			len -= n2;

			/*
			 * If current second code point is out of decomposable
			 * code points, finding compositions is unneeded.
			 */
			if (!IS_DECOMPOSABLE_BLOCK(uc2)) {
				WRITE_UC();
				REPLACE_UC_WITH_UC2();
				continue;
			}

			/*
			 * Try to combine current code points.
			 */
			/*
			 * We have to combine Hangul characters according to
			 * http://uniicode.org/reports/tr15/#Hangul
			 */
			if (0 <= (LIndex = uc - HC_LBASE) &&
			    LIndex < HC_LCOUNT) {
				/*
				 * Hangul Composition.
				 * 1. Two current code points are L and V.
				 */
				int VIndex = uc2 - HC_VBASE;
				if (0 <= VIndex && VIndex < HC_VCOUNT) {
					/* Make syllable of form LV. */
					UPDATE_UC(HC_SBASE +
					    (LIndex * HC_VCOUNT + VIndex) *
					     HC_TCOUNT);
				} else {
					WRITE_UC();
					REPLACE_UC_WITH_UC2();
				}
				continue;
			} else if (0 <= (SIndex = uc - HC_SBASE) &&
			    SIndex < HC_SCOUNT && (SIndex % HC_TCOUNT) == 0) {
				/*
				 * Hangul Composition.
				 * 2. Two current code points are LV and T.
				 */
				int TIndex = uc2 - HC_TBASE;
				if (0 < TIndex && TIndex < HC_TCOUNT) {
					/* Make syllable of form LVT. */
					UPDATE_UC(uc + TIndex);
				} else {
					WRITE_UC();
					REPLACE_UC_WITH_UC2();
				}
				continue;
			} else if ((nfc = get_nfc(uc, uc2)) != 0) {
				/* A composition to current code points
				 * is found. */
				UPDATE_UC(nfc);
				continue;
			} else if ((cl = CCC(uc2)) == 0) {
				/* Clearly 'uc2' the second code point is not
				 * a decomposable code. */
				WRITE_UC();
				REPLACE_UC_WITH_UC2();
				continue;
			}

			/*
			 * Collect following decomposable code points.
			 */
			cx = 0;
			ucx[0] = uc2;
			ccx[0] = cl;
			COLLECT_CPS(1);

			/*
			 * Find a composed code in the collected code points.
			 */
			i = 1;
			while (i < ucx_size) {
				int j;

				if ((nfc = get_nfc(uc, ucx[i])) == 0) {
					i++;
					continue;
				}

				/*
				 * nfc is composed of uc and ucx[i].
				 */
				UPDATE_UC(nfc);

				/*
				 * Remove ucx[i] by shifting
				 * following code points.
				 */
				for (j = i; j+1 < ucx_size; j++) {
					ucx[j] = ucx[j+1];
					ccx[j] = ccx[j+1];
				}
				ucx_size --;

				/*
				 * Collect following code points blocked
				 * by ucx[i] the removed code point.
				 */
				if (ucx_size > 0 && i == ucx_size &&
				    nx > 0 && cx == cl) {
					cl =  ccx[ucx_size-1];
					COLLECT_CPS(ucx_size);
				}
				/*
				 * Restart finding a composed code with
				 * the updated uc from the top of the
				 * collected code points.
				 */
				i = 0;
			}

			/*
			 * Apparently the current code points are not
			 * decomposed characters or already composed.
			 */
			WRITE_UC();
			for (i = 0; i < ucx_size; i++)
				UNPARSE(p, endp, ucx[i]);

			/*
			 * Flush out remaining canonical combining characters.
			 */
			if (nx > 0 && cx == cl && len > 0) {
				while ((nx = parse(&ucx[0], s, len))
				    > 0) {
					cx = CCC(ucx[0]);
					if (cl > cx)
						break;
					s += nx;
					len -= nx;
					cl = cx;
					UNPARSE(p, endp, ucx[0]);
				}
			}
			break;
		}
		if (n2 < 0) {
			WRITE_UC();
			/* Use a replaced unicode character. */
			UNPARSE(p, endp, uc2);
			s += n2*-1;
			len -= n2*-1;
			ret = -1;
			continue;
		} else if (n2 == 0) {
			WRITE_UC();
			break;
		}
	}