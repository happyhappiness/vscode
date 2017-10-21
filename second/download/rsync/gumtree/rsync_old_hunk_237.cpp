    exit_cleanup(1);
  }

  sum_end(file_sum1);

  if (remote_version >= 14) {
    read_buf(f_in,file_sum2,SUM_LENGTH);
    if (verbose > 2)
      fprintf(FERROR,"got file_sum\n");
    if (memcmp(file_sum1,file_sum2,SUM_LENGTH) != 0)
      return 0;
  }
  return 1;
}


