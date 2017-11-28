void
ACLIntRange::parse()
{
    char *a;

    while ((a = strtokFile())) {
        char *b = strchr(a, '-');
        unsigned short port1, port2;

        if (b)
            *b++ = '\0';

        port1 = xatos(a);

        if (b)
            port2 = xatos(b);
        else
            port2 = port1;

        if (port2 >= port1) {
            RangeType temp (0,0);
            temp.start = port1;
            temp.end = port2+1;
            ranges.push_back(temp);
        } else {
            debugs(28, 0, "ACLIntRange::parse: Invalid port value");
            self_destruct();
        }
    }
}