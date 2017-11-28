static int
wordchar_p(const char *d, const char *end1, const char *string2)
{
    return re_syntax_table[(d) == end1 ? *string2
                           : (d) == string2 - 1 ? *(end1 - 1) : *(d)]
           == Sword;
}