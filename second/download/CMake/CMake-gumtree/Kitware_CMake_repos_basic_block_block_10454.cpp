{
					if (!uuchar[b[0]] || !uuchar[b[1]])
						break;
					n = UUDECODE(*b++) << 18;
					n |= UUDECODE(*b++) << 12;
					*out++ = n >> 16; total++;
					--l;
				}