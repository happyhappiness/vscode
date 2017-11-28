void Adaptation::Icap::Xaction::noteCommClosed(const CommCloseCbParams &)
{
    if (securer != NULL) {
        securer->cancel("Connection closed before SSL negotiation finished");
        securer = NULL;
    }
    closer = NULL;
    handleCommClosed();
}