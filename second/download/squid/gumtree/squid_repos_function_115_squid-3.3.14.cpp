const char *
make_nam(int id, int size)
{
    const char *buf = malloc(30);	/* argh */
    sprintf((char *) buf, "pl:%d/%d", id, size);
    return buf;
}