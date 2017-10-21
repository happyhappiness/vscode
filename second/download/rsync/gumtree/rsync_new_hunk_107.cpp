    if (!buf) out_of_memory("read_write");
  }

  while (total < size) {
    int n = MIN(size-total,bufsize);
    read_buf(fd_in,buf,n);
    if (write_sparse(fd_out,buf,n) != n)
      return total;
    total += n;
  }
  return total;
}

