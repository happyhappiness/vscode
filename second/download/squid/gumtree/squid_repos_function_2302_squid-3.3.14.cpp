static int
idnsFromKnownNameserver(Ip::Address const &from)
{
    int i;

    for (i = 0; i < nns; ++i) {
        if (nameservers[i].S != from)
            continue;

        if (nameservers[i].S.GetPort() != from.GetPort())
            continue;

        return i;
    }

    return -1;
}