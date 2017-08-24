(s[0] == '%' && s[1] != '\0' && s[2] != '\0') {
			/* Try to convert % escape */
			int digit1 = tohex(s[1]);
			int digit2 = tohex(s[2]);
			if (digit1 >= 0 && digit2 >= 0) {
				/* Looks good, consume three chars */
				s += 3;
				/* Convert output */
				*d++ = ((digit1 << 4) | digit2);
				continue;
			}
			/* Else fall through and treat '%' as normal char */
		}