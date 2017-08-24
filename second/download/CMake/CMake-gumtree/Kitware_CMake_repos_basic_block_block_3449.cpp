{
      BZ2_bsInitWrite ( s );
      bsPutUChar ( s, BZ_HDR_B );
      bsPutUChar ( s, BZ_HDR_Z );
      bsPutUChar ( s, BZ_HDR_h );
      bsPutUChar ( s, (UChar)(BZ_HDR_0 + s->blockSize100k) );
   }