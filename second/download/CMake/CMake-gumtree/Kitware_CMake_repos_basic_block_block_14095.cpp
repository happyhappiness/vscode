{
		int m = (t + b) / 2;
		if (u_decomposition_table[m].nfc < uc)
			t = m + 1;
		else if (u_decomposition_table[m].nfc > uc)
			b = m - 1;
		else {
			*cp1 = u_decomposition_table[m].cp1;
			*cp2 = u_decomposition_table[m].cp2;
			return (1);
		}
	}