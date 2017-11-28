unsigned int TextException::FileNameHash(const char *fname)
{
    const char *s = NULL;
    unsigned int n = 0;
    unsigned int j = 0;
    unsigned int i = 0;
    s = strrchr(fname, '/');

    if (s)
        ++s;
    else
        s = fname;

    while (*s) {
        ++j;
        n ^= 271 * (unsigned) *s;
        ++s;
    }
    i = n ^ (j * 271);
    /*18bits of a 32 bit integer used  for filename hash (max hash=262143),
      and 14 bits for storing line number (16k max).
      If you change this policy remember to update the FileNameHash function
      in the scripts/calc-must-ids.pl script
    */
    return i % 262143;
}