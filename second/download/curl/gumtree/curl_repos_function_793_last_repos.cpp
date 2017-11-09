static void SHA256_Final(unsigned char digest[32], SHA256_CTX *ctx)
{
  sha256_digest(ctx, 32, digest);
}