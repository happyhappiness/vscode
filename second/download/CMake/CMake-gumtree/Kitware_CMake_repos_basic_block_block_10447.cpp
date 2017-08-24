(l > 0) {
					if (!base64[b[0]] || !base64[b[1]])
						break;
					n = base64num[*b++] << 18;
					n |= base64num[*b++] << 12;
					*out++ = n >> 16; total++;
					l -= 2;
				}