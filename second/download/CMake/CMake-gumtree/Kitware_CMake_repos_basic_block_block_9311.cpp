{
			int r1 = (f->close)(f);
			f->closed = 1;
			if (r1 < r)
				r = r1;
		}