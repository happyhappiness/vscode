static int looks_like_an_argument(const char *word)
{
    return ap_strchr(ARG_PREFIX, *word) != 0;
}