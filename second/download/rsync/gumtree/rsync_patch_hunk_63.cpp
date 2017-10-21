       }
 
       if (!am_server && verbose)
 	printf("%s\n",fname);
 
       /* recv file data */
-      receive_data(f_in,buf,fd2);
+      receive_data(f_in,buf,fd2,fname);
 
       close(fd1);
       close(fd2);
 
       if (verbose > 2)
 	fprintf(stderr,"renaming %s to %s\n",fnametmp,fname);
