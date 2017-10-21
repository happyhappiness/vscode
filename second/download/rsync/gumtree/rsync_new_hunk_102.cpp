	len = remainder;

      if (verbose > 3)
	fprintf(stderr,"chunk[%d] of size %d at %d offset=%d\n",
		i,len,(int)offset2,(int)offset);

      if (write(fd,map_ptr(buf,offset2,len),len) != len) {
	fprintf(stderr,"write failed on %s : %s\n",fname,strerror(errno));
	exit(1);
      }
      offset += len;
    }
  }
