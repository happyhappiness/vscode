void
 MDupdate(MDp,X,count)
 MDptr MDp;
 unsigned char *X;
 unsigned int count;
 { unsigned int32 i, tmp, bit, byte, mask;
   unsigned char XX[64];
   unsigned char *p;
   /* return with no error if this is a courtesy close with count
   ** zero and MDp->done is true.
   */
   if (count == 0 && MDp->done) return;
   /* check to see if MD is already done and report error */
   if (MDp->done)
          { printf("\nError: MDupdate MD already done."); return; }
   /* Add count to MDp->count */
   tmp = count;
   p = MDp->count;
   while (tmp)
     { tmp += *p;
       *p++ = tmp;
       tmp = tmp >> 8;
     }
   /* Process data */
   if (count == 512)
     { /* Full block of data to handle */
       MDblock(MDp,(unsigned int *)X);
     }
   else if (count > 512) /* Check for count too large */
     { printf("\nError: MDupdate called with illegal count value %d."
              ,count);
       return;
     }
   else /* partial block -- must be last block so finish up */
     { /* Find out how many bytes and residual bits there are */
       byte = count >> 3;
       bit =  count & 7;
       /* Copy X into XX since we need to modify it */
       for (i=0;i<=byte;i++)   XX[i] = X[i];
       for (i=byte+1;i<64;i++) XX[i] = 0;
       /* Add padding '1' bit and low-order zeros in last byte */
       mask = 1 << (7 - bit);
       XX[byte] = (XX[byte] | mask) & ~( mask - 1);
       /* If room for bit count, finish up with this block */
       if (byte <= 55)
         { for (i=0;i<8;i++) XX[56+i] = MDp->count[i];
           MDblock(MDp,(unsigned int32 *)XX);
         }
       else /* need to do two blocks to finish up */
         { MDblock(MDp,(unsigned int32 *)XX);
           for (i=0;i<56;i++) XX[i] = 0;
           for (i=0;i<8;i++)  XX[56+i] = MDp->count[i];
           MDblock(MDp,(unsigned int32 *)XX);
         }
       /* Set flag saying we're done with MD computation */
       MDp->done = 1;
     }
 }