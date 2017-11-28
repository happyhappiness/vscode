void
dumpstack (stackmember * stack, int depth)
{
    int i;

    for (i = 0; i < depth; ++i)
        printmember (stack[i]);

    if (depth)
        debug (86,1) ("\n");
}