(;*p; p++) {
			if (*p & 0x80) {
				*p = '_';
				continue;
			}
			if (char_map[(unsigned char)*p]) {
				/* if iso-level is '4', a character '.' is
				 * allowed by char_map. */
				if (*p == '.') {
					xdot = dot;
					dot = p;
				}
				continue;
			}
			if (*p >= 'a' && *p <= 'z') {
				*p -= 'a' - 'A';
				continue;
			}
			if (*p == '.') {
				xdot = dot;
				dot = p;
				if (allow_multidot)
					continue;
			}
			*p = '_';
		}