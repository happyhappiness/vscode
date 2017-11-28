void
HttpRequest::recordLookup(const DnsLookupDetails &dns)
{
    if (dns.wait >= 0) { // known delay
        if (dnsWait >= 0) // have recorded DNS wait before
            dnsWait += dns.wait;
        else
            dnsWait = dns.wait;
    }
}