static void generate_salt(char *s, size_t size)
{
    static unsigned char tbl[] = 
        "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    size_t i;
    for (i = 0; i < size; ++i) {
        int idx = (int) (64.0 * rand() / (RAND_MAX + 1.0));
        s[i] = tbl[idx];
    }
}