      if (verbose > 3)
	fprintf(stderr,"chunk[%d] of size %d at %d offset=%d\n",
		i,len,(int)offset2,(int)offset);

      if (write_sparse(fd,map_ptr(buf,offset2,len),len) != len) {
	fprintf(stderr,"write failed on %s : %s\n",fname,strerror(errno));
	exit(1);
      }
      offset += len;
    }
  }

  if (offset > 0 && sparse_end(fd) != 0) {
    fprintf(stderr,"write failed on %s : %s\n",fname,strerror(errno));
    exit(1);
  }
}


static void delete_one(struct file_struct *f)
{
