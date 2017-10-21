    /* Process data */
    if (count == 512)
      { /* Full block of data to handle */
        MDblock(MDp,(unsigned int *)X);
      }
    else if (count > 512) /* Check for count too large */
-     { printf("\nError: MDupdate called with illegal count value %d."
+     { fprintf(FERROR,"\nError: MDupdate called with illegal count value %d."
               ,count);
        return;
      }
    else /* partial block -- must be last block so finish up */
      { /* Find out how many bytes and residual bits there are */
        byte = count >> 3;
