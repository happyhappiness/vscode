static const void *body(MD4_CTX *ctx, const void *data, unsigned long size)
{
  const unsigned char *ptr;
  MD4_u32plus a, b, c, d;
  MD4_u32plus saved_a, saved_b, saved_c, saved_d;

  ptr = (const unsigned char *)data;

  a = ctx->a;
  b = ctx->b;
  c = ctx->c;
  d = ctx->d;

  do {
    saved_a = a;
    saved_b = b;
    saved_c = c;
    saved_d = d;

/* Round 1 */
    STEP(F, a, b, c, d, SET(0), 3)
      STEP(F, d, a, b, c, SET(1), 7)
      STEP(F, c, d, a, b, SET(2), 11)
      STEP(F, b, c, d, a, SET(3), 19)
      STEP(F, a, b, c, d, SET(4), 3)
      STEP(F, d, a, b, c, SET(5), 7)
      STEP(F, c, d, a, b, SET(6), 11)
      STEP(F, b, c, d, a, SET(7), 19)
      STEP(F, a, b, c, d, SET(8), 3)
      STEP(F, d, a, b, c, SET(9), 7)
      STEP(F, c, d, a, b, SET(10), 11)
      STEP(F, b, c, d, a, SET(11), 19)
      STEP(F, a, b, c, d, SET(12), 3)
      STEP(F, d, a, b, c, SET(13), 7)
      STEP(F, c, d, a, b, SET(14), 11)
      STEP(F, b, c, d, a, SET(15), 19)

/* Round 2 */
      STEP(G, a, b, c, d, GET(0) + 0x5a827999, 3)
      STEP(G, d, a, b, c, GET(4) + 0x5a827999, 5)
      STEP(G, c, d, a, b, GET(8) + 0x5a827999, 9)
      STEP(G, b, c, d, a, GET(12) + 0x5a827999, 13)
      STEP(G, a, b, c, d, GET(1) + 0x5a827999, 3)
      STEP(G, d, a, b, c, GET(5) + 0x5a827999, 5)
      STEP(G, c, d, a, b, GET(9) + 0x5a827999, 9)
      STEP(G, b, c, d, a, GET(13) + 0x5a827999, 13)
      STEP(G, a, b, c, d, GET(2) + 0x5a827999, 3)
      STEP(G, d, a, b, c, GET(6) + 0x5a827999, 5)
      STEP(G, c, d, a, b, GET(10) + 0x5a827999, 9)
      STEP(G, b, c, d, a, GET(14) + 0x5a827999, 13)
      STEP(G, a, b, c, d, GET(3) + 0x5a827999, 3)
      STEP(G, d, a, b, c, GET(7) + 0x5a827999, 5)
      STEP(G, c, d, a, b, GET(11) + 0x5a827999, 9)
      STEP(G, b, c, d, a, GET(15) + 0x5a827999, 13)

/* Round 3 */
      STEP(H, a, b, c, d, GET(0) + 0x6ed9eba1, 3)
      STEP(H, d, a, b, c, GET(8) + 0x6ed9eba1, 9)
      STEP(H, c, d, a, b, GET(4) + 0x6ed9eba1, 11)
      STEP(H, b, c, d, a, GET(12) + 0x6ed9eba1, 15)
      STEP(H, a, b, c, d, GET(2) + 0x6ed9eba1, 3)
      STEP(H, d, a, b, c, GET(10) + 0x6ed9eba1, 9)
      STEP(H, c, d, a, b, GET(6) + 0x6ed9eba1, 11)
      STEP(H, b, c, d, a, GET(14) + 0x6ed9eba1, 15)
      STEP(H, a, b, c, d, GET(1) + 0x6ed9eba1, 3)
      STEP(H, d, a, b, c, GET(9) + 0x6ed9eba1, 9)
      STEP(H, c, d, a, b, GET(5) + 0x6ed9eba1, 11)
      STEP(H, b, c, d, a, GET(13) + 0x6ed9eba1, 15)
      STEP(H, a, b, c, d, GET(3) + 0x6ed9eba1, 3)
      STEP(H, d, a, b, c, GET(11) + 0x6ed9eba1, 9)
      STEP(H, c, d, a, b, GET(7) + 0x6ed9eba1, 11)
      STEP(H, b, c, d, a, GET(15) + 0x6ed9eba1, 15)

      a += saved_a;
    b += saved_b;
    c += saved_c;
    d += saved_d;

    ptr += 64;
  } while(size -= 64);

  ctx->a = a;
  ctx->b = b;
  ctx->c = c;
  ctx->d = d;

  return ptr;
}