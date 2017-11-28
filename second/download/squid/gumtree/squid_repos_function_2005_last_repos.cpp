void
httpHdrCcInitModule(void)
{
    // check invariant on initialization table
    for (unsigned int j = 0; CcAttrs[j].name != nullptr; ++j) {
        assert (static_cast<int>(CcAttrs[j].id) == j);
    }
}