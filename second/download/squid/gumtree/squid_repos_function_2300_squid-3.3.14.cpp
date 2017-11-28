static void
idnsSendQueryVC(idns_query * q, int ns)
{
    assert(ns < nns);
    if (nameservers[ns].vc == NULL)
        idnsInitVC(ns);

    nsvc *vc = nameservers[ns].vc;

    if (!vc) {
        char buf[MAX_IPSTRLEN];
        debugs(78, DBG_IMPORTANT, "idnsSendQuery: Failed to initiate TCP connection to nameserver " << nameservers[ns].S.NtoA(buf,MAX_IPSTRLEN) << "!");

        return;
    }

    vc->queue->reset();

    short head = htons(q->sz);

    vc->queue->append((char *)&head, 2);

    vc->queue->append(q->buf, q->sz);

    idnsDoSendQueryVC(vc);
}