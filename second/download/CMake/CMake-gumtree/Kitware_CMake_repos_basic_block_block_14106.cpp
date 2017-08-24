{
			int k;

			for (k = fdi; k > 0; k--)
				fdc[k] = fdc[k-1];
			fdc[0].ccc = CCC(cp2);
			fdc[0].uc = cp2;
			fdi++;
			REPLACE_UC_WITH(cp1);
		}