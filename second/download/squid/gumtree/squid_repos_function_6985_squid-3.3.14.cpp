inline
int open(const char *filename, int oflag, int pmode = 0)
{
    return _open(filename, oflag, pmode & (_S_IREAD | _S_IWRITE));
}