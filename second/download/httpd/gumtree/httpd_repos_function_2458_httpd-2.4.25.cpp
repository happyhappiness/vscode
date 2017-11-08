static void sha256_update(SHA256_CTX *ctx, const char *s)
{
    SHA256_Update(ctx, s, strlen(s));
}