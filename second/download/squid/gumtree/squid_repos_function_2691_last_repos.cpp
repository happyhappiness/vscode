inline long int tvToMsec(struct timeval &t)
{
    return t.tv_sec * 1000 + t.tv_usec / 1000;
}