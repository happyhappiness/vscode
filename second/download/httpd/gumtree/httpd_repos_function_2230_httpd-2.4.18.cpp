void h2_util_camel_case_header(char *s, size_t len)
{
    size_t start = 1;
    size_t i;
    for (i = 0; i < len; ++i) {
        if (start) {
            if (s[i] >= 'a' && s[i] <= 'z') {
                s[i] -= 'a' - 'A';
            }
            
            start = 0;
        }
        else if (s[i] == '-') {
            start = 1;
        }
    }
}