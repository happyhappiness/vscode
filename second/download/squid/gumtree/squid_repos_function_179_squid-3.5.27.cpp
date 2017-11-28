const char *
make_nam(int id, int size)
{
    const char *buf = malloc(30);   /* argh */
    snprintf((char *)buf, sizeof(buf)-1, "pl:%d/%d", id, size);
    return buf;
}