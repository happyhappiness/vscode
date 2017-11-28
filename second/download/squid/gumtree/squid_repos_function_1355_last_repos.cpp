void
httpHdrScInitModule(void)
{
    // check invariant on ScAttrs
    for (int i = 0; ScAttrs[i].name != nullptr; ++i)
        assert(i == ScAttrs[i].id);
}