fprintf(stderr,"s2:s1 = %.4x%.4x sum=%.8x k=%d offset=%d took %x added %x\n",
	      s2&0xffff, s1&0xffff, get_checksum1(buf+offset+1,k),
	      k, (int)offset, buf[offset], buf[offset+k]);