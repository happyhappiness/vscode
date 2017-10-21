 	fprintf(stderr,"rename %s -> %s : %s\n",
 		fnametmp,fname,strerror(errno));
       }
 
       cleanup_fname = NULL;
 
-      unmap_file(buf,st.st_size);
-
       set_perms(fname,&flist->files[i],NULL,0);
     }
 
   if (verbose > 2)
     fprintf(stderr,"recv_files finished\n");
   
