void
 MDbegin(MDp)
 MDptr MDp;
 { int i;
   MDp->buffer[0] = I0;
   MDp->buffer[1] = I1;
   MDp->buffer[2] = I2;
   MDp->buffer[3] = I3;
   for (i=0;i<8;i++) MDp->count[i] = 0;
   MDp->done = 0;
 }