        if (csum_length == SUM_LENGTH)
	  fprintf(FERROR,"ERROR: file corruption in %s\n",fname);
	write_int(f_gen,i);
      }
    }

  if (verbose > 2)
    fprintf(FERROR,"recv_files finished\n");
  
  return 0;
}

