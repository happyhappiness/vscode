static int
_my_wcslen(int16_t * str)
{
    int len = 0;
    while (*str++ != 0)
        len++;
    return len;
}