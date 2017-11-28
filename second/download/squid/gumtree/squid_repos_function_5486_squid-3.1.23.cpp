void
stackpop (stackmember * s, int *depth)
{
    if (!(*depth)--)
        return;

    cleanmember (&s[*depth]);
}