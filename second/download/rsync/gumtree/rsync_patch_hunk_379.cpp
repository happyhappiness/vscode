 	      else 
 		      f++;
 	      sprintf(fnametmp,"%s/%s.XXXXXX",tmpdir,f);
       } else {
 	      sprintf(fnametmp,"%s.XXXXXX",fname);
       }
-      if (NULL == mktemp(fnametmp)) {
+      if (NULL == do_mktemp(fnametmp)) {
 	fprintf(FERROR,"mktemp %s failed\n",fnametmp);
 	receive_data(f_in,buf,-1,NULL);
 	if (buf) unmap_file(buf);
 	close(fd1);
 	continue;
       }
