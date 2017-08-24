{
				unsigned char *wb;

				wb = wb_buffptr(a);
				memcpy(wb, extr->buf, extr->offset);
				memset(wb + extr->offset, 0,
				    LOGICAL_BLOCK_SIZE - extr->offset);
				r = wb_consume(a, LOGICAL_BLOCK_SIZE);
				if (r < 0)
					return (r);
			}