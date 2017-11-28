inline const char *bumpMode(int bm)
{
    return (0 <= bm && bm < Ssl::bumpEnd) ? Ssl::BumpModeStr[bm] : NULL;
}