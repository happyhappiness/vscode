 
     s->sums[i].offset = offset;
     s->sums[i].len = n1;
     s->sums[i].i = i;
 
     if (verbose > 3)
-      fprintf(FERROR,"chunk[%d] offset=%d len=%d sum1=%08x\n",
+      fprintf(FINFO,"chunk[%d] offset=%d len=%d sum1=%08x\n",
 	      i,(int)s->sums[i].offset,s->sums[i].len,s->sums[i].sum1);
 
     len -= n1;
     offset += n1;
   }
 
