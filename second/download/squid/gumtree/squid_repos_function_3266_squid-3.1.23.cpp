static oid *
client_Inst(oid * name, snint * len, mib_tree_entry * current, oid_ParseFn ** Fn)
{
    oid *instance = NULL;
    IpAddress laddr;
    IpAddress *aux;
    int size = 0;
    int newshift = 0;

    if (*len <= current->len) {
        aux  = client_entry(NULL);
        if (aux)
            laddr = *aux;
        else
            laddr.SetAnyAddr();

        if (laddr.IsIPv4())
            size = sizeof(in_addr);
        else
            size = sizeof(in6_addr);

        debugs(49, 6, HERE << "len" << *len << ", current-len" << current->len << ", addr=" << laddr << ", size=" << size);

        instance = (oid *)xmalloc(sizeof(name) * (*len + size ));
        xmemcpy(instance, name, (sizeof(name) * (*len)));

        if ( !laddr.IsAnyAddr() ) {
            addr2oid(laddr, &instance[ *len]);  // the addr
            *len += size ;
        }
    } else {
        int shift = *len - current->len ; // i.e 4 or 16
        oid2addr(&name[*len - shift], laddr,shift);
        aux = client_entry(&laddr);
        if (aux)
            laddr = *aux;
        else
            laddr.SetAnyAddr();

        if (!laddr.IsAnyAddr()) {
            if (laddr.IsIPv4())
                newshift = sizeof(in_addr);
            else
                newshift = sizeof(in6_addr);

            debugs(49, 6, HERE << "len" << *len << ", current-len" << current->len << ", addr=" << laddr << ", newshift=" << newshift);

            instance = (oid *)xmalloc(sizeof(name) * (current->len +  newshift));
            xmemcpy(instance, name, (sizeof(name) * (current->len)));
            addr2oid(laddr, &instance[current->len]);  // the addr.
            *len = current->len + newshift ;
        }
    }

    *Fn = current->parsefunction;
    return (instance);
}