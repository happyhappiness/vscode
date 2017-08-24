{
				/* Looks good, consume three chars */
				s += 3;
				/* Convert output */
				*d++ = ((digit1 << 4) | digit2);
				continue;
			}