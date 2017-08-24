(buff == NULL) {
				/* Remaining bytes are less than window. */
				window >>= 1;
				if (window < 0x40)
					return (0);
				continue;
			}