static int compradre(struct data * a, struct data * b)
{
    if ((a->ctime) < (b->ctime))
        return -1;
    if ((a->ctime) > (b->ctime))
        return +1;
    return 0;
}