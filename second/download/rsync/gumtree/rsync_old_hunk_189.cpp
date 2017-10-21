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
