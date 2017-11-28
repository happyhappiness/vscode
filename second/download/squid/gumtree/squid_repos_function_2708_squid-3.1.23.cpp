void
TunnelStateData::Connection::dataSent (size_t amount)
{
    assert(amount == (size_t)len);
    len =0;
    /* increment total object size */

    if (size_ptr)
        *size_ptr += amount;
}