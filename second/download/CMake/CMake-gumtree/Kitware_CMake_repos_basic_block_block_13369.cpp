{
			if (base64[*b] < 0)
				break;
			n |= base64[*b++] << 6;
			*out++ = (n >> 8) & 0xFF;
			len++;
			--l;
		}