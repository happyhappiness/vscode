{
		if (*len + 2 > max)
			return (-1);/* Path is too long! */
		p[*len] = 0;
		p[*len + 1] = '.';
		*len += 2;
	}