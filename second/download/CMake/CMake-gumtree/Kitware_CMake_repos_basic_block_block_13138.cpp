(p[1] >= 'a' && p[1] <= 'z')
			x |= p[1] - 'a' + 0x0a;
		else if (p[1] >= 'A' && p[1] <= 'Z')
			x |= p[1] - 'A' + 0x0a;
		else if (p[1] >= '0' && p[1] <= '9')
			x |= p[1] - '0';
		else
			return (-1);