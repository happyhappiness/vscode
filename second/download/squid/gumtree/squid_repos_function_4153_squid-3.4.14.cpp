void Adaptation::Icap::Xaction::noteCommClosed(const CommCloseCbParams &io)
{
    closer = NULL;
    handleCommClosed();
}