static char *double_quotes(apr_pool_t *pool, const char *str)
{
    int num_quotes = 0;
    int len = 0;
    char *quote_doubled_str, *dest;
    
    while (str[len]) {
        num_quotes += str[len++] == '\"';
    }
    
    quote_doubled_str = apr_palloc(pool, len + num_quotes + 1);
    dest = quote_doubled_str;
    
    while (*str) {
        if (*str == '\"')
            *(dest++) = '\"';
        *(dest++) = *(str++);
    }
    
    *dest = 0;
    return quote_doubled_str;
}