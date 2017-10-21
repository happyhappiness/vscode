      if (verbose > 2)
	fprintf(stderr,"sender finished %s\n",fname);

      total += st.st_size;
    }

  match_report();

  write_int(f_out,-1);
  write_flush(f_out);

  return total;
}

