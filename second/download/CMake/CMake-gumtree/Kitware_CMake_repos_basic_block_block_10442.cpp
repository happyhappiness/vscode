{
					if (*b == '=')
						break;
					if (!base64[*b])
						break;
					n |= base64num[*b++] << 6;
					*out++ = (n >> 8) & 0xFF; total++;
					--l;
				}