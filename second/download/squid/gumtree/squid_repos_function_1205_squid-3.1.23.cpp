mem_type &operator++ (mem_type &aMem)
{
    int tmp = (int)aMem;
    aMem = (mem_type)(++tmp);
    return aMem;
}