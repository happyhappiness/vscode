void
dumpstack(stackmember * stack, int depth)
{
    if (depth) {
        std::ostringstream buf;
        for (int i = 0; i < depth; ++i)
            buf << stack[i];
        debugs(86,1, buf.str());
    }
}