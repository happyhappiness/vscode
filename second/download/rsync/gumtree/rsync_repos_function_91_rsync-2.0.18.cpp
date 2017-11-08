static void
 MDblock(MDp,X)
 MDptr MDp;
 unsigned int32 *X;
 {
   register unsigned int32 tmp, A, B, C, D;
   MDreverse(X);
   A = MDp->buffer[0];
   B = MDp->buffer[1];
   C = MDp->buffer[2];
   D = MDp->buffer[3];
   /* Update the message digest buffer */
   ff(A , B , C , D ,  0 , fs1); /* Round 1 */
   ff(D , A , B , C ,  1 , fs2);
   ff(C , D , A , B ,  2 , fs3);
   ff(B , C , D , A ,  3 , fs4);
   ff(A , B , C , D ,  4 , fs1);
   ff(D , A , B , C ,  5 , fs2);
   ff(C , D , A , B ,  6 , fs3);
   ff(B , C , D , A ,  7 , fs4);
   ff(A , B , C , D ,  8 , fs1);
   ff(D , A , B , C ,  9 , fs2);
   ff(C , D , A , B , 10 , fs3);
   ff(B , C , D , A , 11 , fs4);
   ff(A , B , C , D , 12 , fs1);
   ff(D , A , B , C , 13 , fs2);
   ff(C , D , A , B , 14 , fs3);
   ff(B , C , D , A , 15 , fs4);
   gg(A , B , C , D ,  0 , gs1); /* Round 2 */
   gg(D , A , B , C ,  4 , gs2);
   gg(C , D , A , B ,  8 , gs3);
   gg(B , C , D , A , 12 , gs4);
   gg(A , B , C , D ,  1 , gs1);
   gg(D , A , B , C ,  5 , gs2);
   gg(C , D , A , B ,  9 , gs3);
   gg(B , C , D , A , 13 , gs4);
   gg(A , B , C , D ,  2 , gs1);
   gg(D , A , B , C ,  6 , gs2);
   gg(C , D , A , B , 10 , gs3);
   gg(B , C , D , A , 14 , gs4);
   gg(A , B , C , D ,  3 , gs1);
   gg(D , A , B , C ,  7 , gs2);
   gg(C , D , A , B , 11 , gs3);
   gg(B , C , D , A , 15 , gs4);
   hh(A , B , C , D ,  0 , hs1); /* Round 3 */
   hh(D , A , B , C ,  8 , hs2);
   hh(C , D , A , B ,  4 , hs3);
   hh(B , C , D , A , 12 , hs4);
   hh(A , B , C , D ,  2 , hs1);
   hh(D , A , B , C , 10 , hs2);
   hh(C , D , A , B ,  6 , hs3);
   hh(B , C , D , A , 14 , hs4);
   hh(A , B , C , D ,  1 , hs1);
   hh(D , A , B , C ,  9 , hs2);
   hh(C , D , A , B ,  5 , hs3);
   hh(B , C , D , A , 13 , hs4);
   hh(A , B , C , D ,  3 , hs1);
   hh(D , A , B , C , 11 , hs2);
   hh(C , D , A , B ,  7 , hs3);
   hh(B , C , D , A , 15 , hs4);
   MDp->buffer[0] += A;
   MDp->buffer[1] += B;
   MDp->buffer[2] += C;
   MDp->buffer[3] += D;
 }