(*src == '.' && p == src + 1) {
		strcpy(dest, "PaxHeader/currentdir");
		return (dest);
	}