void
httpHeaderUpdate(HttpHeader * old, const HttpHeader * fresh, const HttpHeaderMask * denied_mask)
{
    assert (old);
    old->update (fresh, denied_mask);
}