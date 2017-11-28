static void
ipcacheHandleCnameRecurse(const ipcache_addrs *addrs, const DnsLookupDetails &, void *cbdata)
{
#if DNS_CNAME
    ipcache_entry *i = NULL;
    char *pname = NULL;
    IpAddress *tmpbuf = NULL;
    int fc = 0;
    int ttl = 0;
    generic_cbdata* gcb = (generic_cbdata*)cbdata;
    // count of addrs at parent and child (REQ as .count is a char type!)
    int ccount = 0, pcount = 0;

    debugs(14, 5, "ipcacheHandleCnameRecurse: Handling basic A/AAAA response.");

    /* IFF no CNAME recursion being processed. do nothing. */
    if (cbdata == NULL)
        return;

    gcb->unwrap(&i);
    assert(i != NULL);

    // make sure we are actualy waiting for a CNAME callback to be run.
    assert(i->cname_wait > 0);
    // count this event. its being handled.
    i->cname_wait--;

    pname = (char*)i->hash.key;
    assert(pname != NULL);

    debugs(14, 5, "ipcacheHandleCnameRecurse: Handling CNAME recursion. CBDATA('" << gcb->data << "')='" << pname << "' -> " << std::hex << i);

    if (i == NULL) {
        return; // Parent has expired. Don't merge, just leave for future Ref:
    }

    /* IFF addrs is NULL (Usually an Error or Timeout occured on lookup.) */
    /* Ignore it and HOPE that we got some Additional records to use.     */
    if (addrs == NULL)
        return;

    ccount = (0+ addrs->count);
    pcount = (0+ i->addrs.count);
    ttl = i->expires;

    /* IFF no CNAME results. do none of the processing BUT finish anyway. */
    if (addrs) {

        debugs(14, 5, "ipcacheHandleCnameRecurse: Merge IP Lists for " << pname << " (" << pcount << "+" << ccount << ")");

        /* add new IP records to entry */
        tmpbuf = i->addrs.in_addrs;
        i->addrs.in_addrs = NULL;
        ipcacheMergeIPLists(tmpbuf, pcount, addrs->in_addrs, ccount, &(i->addrs.in_addrs), fc);
        debugs(14,8, HERE << "in=" << tmpbuf << ", out=" << i->addrs.in_addrs );
        assert( (pcount>0 ? tmpbuf!=NULL : tmpbuf==NULL) );
        safe_free(tmpbuf);

        if ( pcount > 0) {
            /* IFF the parent initial lookup was given Additional records with A */
            // clear the 'bad IP mask'
            safe_free(i->addrs.bad_mask);
        }
        // create a new bad IP mask to fit the new size needed.
        if (fc > 0) {
            i->addrs.bad_mask = (unsigned char*)xcalloc(fc, sizeof(unsigned char));
            memset(i->addrs.bad_mask, 0, sizeof(unsigned char)*fc);
        }

        if (fc < 256)
            i->addrs.count = (unsigned char) fc;
        else
            i->addrs.count = 255;

        if (ttl == 0 || ttl > Config.positiveDnsTtl)
            ttl = Config.positiveDnsTtl;

        if (ttl < Config.negativeDnsTtl)
            ttl = Config.negativeDnsTtl;

        i->expires = squid_curtime + ttl;

        i->flags.negcached = 0;

        i->addrs.cur = 0;

        i->addrs.badcount = 0;
    }

    if (fc == 0) {
        i->error_message = xstrdup("No DNS Records");
    }

    /* finish the lookup we were doing on parent when we got side-tracked for CNAME loop */
    if (i->cname_wait == 0) {
        ipcacheAddEntry(i);
        ipcacheCallback(i, i->age()); // age since i creation, includes CNAMEs
    }
    // else still more CNAME to be found.
#endif /* DNS_CNAME */
}