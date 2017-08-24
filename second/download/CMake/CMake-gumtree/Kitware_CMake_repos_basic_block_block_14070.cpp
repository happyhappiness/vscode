{
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