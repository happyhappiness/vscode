(zisofs->header_avail < sizeof(zisofs->header)) {
			xsize = sizeof(zisofs->header) - zisofs->header_avail;
			if (avail < xsize)
				xsize = avail;
			memcpy(zisofs->header + zisofs->header_avail, p, xsize);
			zisofs->header_avail += xsize;
			avail -= xsize;
			p += xsize;
		}