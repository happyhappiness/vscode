(nbytes_in_lo32 == 0 && nbytes_in_hi32 == 0) {
     fprintf ( stderr, " no data compressed.\n");
      } else {
     Char   buf_nin[32], buf_nout[32];
     UInt64 nbytes_in,   nbytes_out;
     double nbytes_in_d, nbytes_out_d;
     uInt64_from_UInt32s ( &nbytes_in, 
                   nbytes_in_lo32, nbytes_in_hi32 );
     uInt64_from_UInt32s ( &nbytes_out, 
                   nbytes_out_lo32, nbytes_out_hi32 );
     nbytes_in_d  = uInt64_to_double ( &nbytes_in );
     nbytes_out_d = uInt64_to_double ( &nbytes_out );
     uInt64_toAscii ( buf_nin, &nbytes_in );
     uInt64_toAscii ( buf_nout, &nbytes_out );
     fprintf ( stderr, "%6.3f:1, %6.3f bits/byte, "
           "%5.2f%% saved, %s in, %s out.\n",
           nbytes_in_d / nbytes_out_d,
           (8.0 * nbytes_out_d) / nbytes_in_d,
           100.0 * (1.0 - nbytes_out_d / nbytes_in_d),
           buf_nin,
           buf_nout
         );
      }