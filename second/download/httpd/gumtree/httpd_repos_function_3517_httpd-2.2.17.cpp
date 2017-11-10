static unsigned int rshash (char *p) {
    /* hash function from Robert Sedgwicks 'Algorithms in C' book */
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int retval = 0;

   for( ; *p; p++)
   {
      retval = retval * a + (*p);
      a *= b;
   }

   return retval;
}