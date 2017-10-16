         else
           fputs("   ", stream);
     }
 
     for(c = 0; (c < width) && (i+c < size); c++) {
       /* check for 0D0A; if found, skip past and start a new line of output */
-      if (nohex && (i+c+1 < size) && ptr[i+c]==0x0D && ptr[i+c+1]==0x0A) {
+      if(nohex && (i+c+1 < size) && ptr[i+c]==0x0D && ptr[i+c+1]==0x0A) {
         i+=(c+2-width);
         break;
       }
       fprintf(stream, "%c",
               (ptr[i+c]>=0x20) && (ptr[i+c]<0x80)?ptr[i+c]:'.');
       /* check again for 0D0A, to avoid an extra \n if it's at width */
-      if (nohex && (i+c+2 < size) && ptr[i+c+1]==0x0D && ptr[i+c+2]==0x0A) {
+      if(nohex && (i+c+2 < size) && ptr[i+c+1]==0x0D && ptr[i+c+2]==0x0A) {
         i+=(c+3-width);
         break;
       }
     }
     fputc('\n', stream); /* newline */
   }
