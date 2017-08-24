{
			long incr = cf->incr_xfer_size;
			/* Some platform does not set a proper value to
			 * incr_xfer_size.*/
			if (incr < 0)
				incr = cf->min_xfer_size;
			if (cf->min_xfer_size < 0) {
				incr = xfer_align;
				asize = xfer_align;
			} else
				asize = cf->min_xfer_size;

			/* Increase a buffer size up to 64K bytes in
			 * a proper increment size. */
			while (asize < 1024*64)
				asize += incr;
			/* Take a margin to adjust to the filesystem
			 * alignment. */
			asize += xfer_align;
		}