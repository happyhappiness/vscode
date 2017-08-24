(i = 0; codes[i].code != 0; i++) {
		if (code == codes[i].code)
			return ((codes[i].setter)(a));
	}