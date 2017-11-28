Security::NegotiationHistory *
Comm::Connection::tlsNegotiations()
{
    if (!tlsHistory)
        tlsHistory = new Security::NegotiationHistory;
    return tlsHistory;
}