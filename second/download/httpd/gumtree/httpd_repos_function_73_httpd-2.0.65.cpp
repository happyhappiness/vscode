static int compwait(struct data * a, struct data * b)
{
    if ((a->waittime) < (b->waittime))
	return -1;
    if ((a->waittime) > (b->waittime))
	return 1;
    return 0;
}