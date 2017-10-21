       i = read_int(f_in);
       if (i == -1) {
 	if (phase==0 && remote_version >= 13) {
 	  phase++;
 	  csum_length = SUM_LENGTH;
 	  if (verbose > 2)
-	    fprintf(FINFO,"recv_files phase=%d\n",phase);
+	    rprintf(FINFO,"recv_files phase=%d\n",phase);
 	  write_int(f_gen,-1);
 	  write_flush(f_gen);
 	  continue;
 	}
 	break;
       }
