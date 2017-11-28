HttpHdrCcType &operator++ (HttpHdrCcType &aHeader)
{
    int tmp = (int)aHeader;
    aHeader = (HttpHdrCcType)(++tmp);
    return aHeader;
}