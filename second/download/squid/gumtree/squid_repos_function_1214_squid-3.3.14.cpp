void
HttpHdrScTarget::updateStats(StatHist * hist) const
{
    http_hdr_sc_type c;

    for (c = SC_NO_STORE; c < SC_ENUM_END; ++c)
        if (isSet(c))
            hist->count(c);
}