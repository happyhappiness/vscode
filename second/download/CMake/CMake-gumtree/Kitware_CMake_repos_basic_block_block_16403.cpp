(0x20 != *s1++)
				return (*(const unsigned char *)(s1 - 1)
				    - 0x20);