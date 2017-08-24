(l > 0) {
			if (base64[b[0]] < 0 || base64[b[1]] < 0)
				break;
			n = base64[*b++] << 18;
			n |= base64[*b++] << 12;
			*out++ = n >> 16;
			len++;
			l -= 2;
		}