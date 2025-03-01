int main ( int argc, char** argv )
{
   FILE* f;
   int   r;
   int   bit;
   int   i;

   if (argc != 2) {
      fprintf ( stderr, "usage: unzcrash filename\n" );
      return 1;
   }

   f = fopen ( argv[1], "r" );
   if (!f) {
      fprintf ( stderr, "unzcrash: can't open %s\n", argv[1] );
      return 1;
   }

   nIn = fread ( inbuf, 1, M_BLOCK, f );
   fprintf ( stderr, "%d bytes read\n", nIn );

   nZ = M_BLOCK;
   r = BZ2_bzBuffToBuffCompress (
         zbuf, &nZ, inbuf, nIn, 9, 0, 30 );

   assert (r == BZ_OK);
   fprintf ( stderr, "%d after compression\n", nZ );

   for (bit = 0; bit < nZ*8; bit++) {
      fprintf ( stderr, "bit %d  ", bit );
      flip_bit ( bit );
      nOut = M_BLOCK_OUT;
      r = BZ2_bzBuffToBuffDecompress (
            outbuf, &nOut, zbuf, nZ, 0, 0 );
      fprintf ( stderr, " %d  %s ", r, bzerrorstrings[-r] );

      if (r != BZ_OK) {
         fprintf ( stderr, "\n" );
      } else {
         if (nOut != nIn) {
           fprintf(stderr, "nIn/nOut mismatch %d %d\n", nIn, nOut );
           return 1;
         } else {
           for (i = 0; i < nOut; i++)
             if (inbuf[i] != outbuf[i]) { 
                fprintf(stderr, "mismatch at %d\n", i ); 
                return 1; 
           }
           if (i == nOut) fprintf(stderr, "really ok!\n" );
         }
      }

      flip_bit ( bit );
   }

#if 0
   assert (nOut == nIn);
   for (i = 0; i < nOut; i++) {
     if (inbuf[i] != outbuf[i]) {
        fprintf ( stderr, "difference at %d !\n", i );
        return 1;
     }
   }
#endif

   fprintf ( stderr, "all ok\n" );
   return 0;
}