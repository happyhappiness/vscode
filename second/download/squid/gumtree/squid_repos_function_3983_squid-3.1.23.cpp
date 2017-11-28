void Adaptation::Icap::Xaction::noteCommConnected(const CommConnectCbParams &io)
{
    Must(connector != NULL);
    connector = NULL;

    if (io.flag != COMM_OK)
        dieOnConnectionFailure(); // throws

    fd_table[connection].noteUse(icapPconnPool);

    handleCommConnected();
}