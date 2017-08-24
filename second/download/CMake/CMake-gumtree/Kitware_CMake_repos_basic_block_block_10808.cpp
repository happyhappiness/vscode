{
				size_t b;
				if (nb > UBUFF_SIZE)
					b = UBUFF_SIZE;
				else
					b = nb;
				if ((p = header_bytes(a, b)) == NULL)
					return (-1);
				memcpy(np, p, b);
				np += b;
				nb -= b;
			}