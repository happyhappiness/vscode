void MDreverse(X)
 unsigned int32 *X;
 { register unsigned int32 t;
   register unsigned int i;

   for(i = 0; i < 16; i++) {
	  t = X[i];
	  SIVAL(X,i*4,t);
	}
 }