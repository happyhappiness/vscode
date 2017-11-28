void
dumpstack(stackmember * stack, int depth)
{
    int i;

    for (i = 0; i < depth; ++i)
        printmember(stack[i]);

    if (depth)
        old_debug(86,1)("\n");
}