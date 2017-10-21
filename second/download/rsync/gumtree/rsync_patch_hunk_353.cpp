       i = read_int(f_in);
       if (i == -1) {
 	if (phase==0 && remote_version >= 13) {
 	  phase++;
 	  csum_length = SUM_LENGTH;
 	  if (verbose > 2)
-	    fprintf(FERROR,"recv_files phase=%d\n",phase);
+	    fprintf(FINFO,"recv_files phase=%d\n",phase);
 	  write_int(f_gen,-1);
 	  write_flush(f_gen);
 	  continue;
 	}
 	break;
       }
 
-      file = &flist->files[i];
-      fname = file->name;
+      file = flist->files[i];
+      fname = f_name(file);
 
       if (local_name)
 	fname = local_name;
 
       if (dry_run) {
 	if (!am_server && verbose)
 	  printf("%s\n",fname);
 	continue;
       }
 
       if (verbose > 2)
-	fprintf(FERROR,"recv_files(%s)\n",fname);
+	fprintf(FINFO,"recv_files(%s)\n",fname);
 
       /* open the file */  
       fd1 = open(fname,O_RDONLY);
 
       if (fd1 != -1 && fstat(fd1,&st) != 0) {
 	fprintf(FERROR,"fstat %s : %s\n",fname,strerror(errno));
