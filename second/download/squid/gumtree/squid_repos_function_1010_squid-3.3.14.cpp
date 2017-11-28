static const char*
skip_ws(const char* s)
{
    while (xisspace(*s))
        ++s;

    return s;
}