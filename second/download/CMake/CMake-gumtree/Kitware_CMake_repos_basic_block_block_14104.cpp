(j < fdi) {
				for (k = fdi; k > j; k--)
					fdc[k] = fdc[k-1];
				fdc[j].ccc = ccc;
				fdc[j].uc = uc2;
			} else {
				fdc[fdi].ccc = ccc;
				fdc[fdi].uc = uc2;
			}