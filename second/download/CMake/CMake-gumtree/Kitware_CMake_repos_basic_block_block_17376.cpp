(i = 0; i < algsize; i++) {
				*p++ = hex[(*s >> 4)];
				*p++ = hex[(*s & 0x0f)];
				s++;
			}