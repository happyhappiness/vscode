{
			int d = *((unsigned char *)p) % sizeof(num);
			*p++ = num[d];
		}