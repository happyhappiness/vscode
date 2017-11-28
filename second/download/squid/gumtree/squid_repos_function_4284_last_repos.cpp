void
ACLIntRange::parse()
{
    while (char *a = ConfigParser::strtokFile()) {
        char *b = strchr(a, '-');
        unsigned short port1, port2;

        if (b) {
            *b = '\0';
            ++b;
        }

        port1 = xatos(a);

        if (b)
            port2 = xatos(b);
        else
            port2 = port1;

        if (port2 >= port1) {
            RangeType temp(port1, port2+1);
            ranges.push_back(temp);
        } else {
            debugs(28, DBG_CRITICAL, "ACLIntRange::parse: Invalid port value");
            self_destruct();
        }
    }
}