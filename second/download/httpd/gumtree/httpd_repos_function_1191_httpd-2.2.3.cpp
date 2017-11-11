static int is_identity_encoding(const char *enc)
{
    return (!enc || !enc[0] || !strcmp(enc, "7bit") || !strcmp(enc, "8bit")
            || !strcmp(enc, "binary"));
}