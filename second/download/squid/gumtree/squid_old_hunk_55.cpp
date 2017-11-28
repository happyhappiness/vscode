    closer = NULL;
    handleCommClosed();
}

void Adaptation::Icap::Xaction::handleCommClosed()
{
    mustStop("ICAP service connection externally closed");
}

void Adaptation::Icap::Xaction::callException(const std::exception  &e)
{
    setOutcome(xoError);
    Adaptation::Initiate::callException(e);
}


void Adaptation::Icap::Xaction::callEnd()
{
