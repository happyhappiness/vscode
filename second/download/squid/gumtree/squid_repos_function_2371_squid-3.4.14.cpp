static void
idnsSendQueryVC(idns_query * q, int nsn)
{
    assert(nsn < nns);
    if (nameservers[nsn].vc == NULL)
        idnsInitVC(nsn);

    nsvc *vc = nameservers[nsn].vc;

    if (!vc) {
        char buf[MAX_IPSTRLEN];
        debugs(78, DBG_IMPORTANT, "idnsSendQuery: Failed to initiate TCP connection to nameserver " << nameservers[nsn].S.toStr(buf,MAX_IPSTRLEN) << "!");

        return;
    }

    vc->queue->reset();

    short head = htons(q->sz);

    vc->queue->append((char *)&head, 2);

    vc->queue->append(q->buf, q->sz);

    idnsDoSendQueryVC(vc);
}