{
			wb = wb_buffptr(a);
			if (size > wb_remaining(a))
				wsize = wb_remaining(a);
			else
				wsize = size;
			memset(wb, 0, wsize);
			r = wb_consume(a, wsize);
			if (r < 0)
				return (r);
			size -= wsize;
		}