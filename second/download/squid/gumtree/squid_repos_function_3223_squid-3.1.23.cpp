const char *
PconnPool::key(const char *host, unsigned short port, const char *domain, IpAddress &client_address)
{
    LOCAL_ARRAY(char, buf, SQUIDHOSTNAMELEN * 3 + 10);
    char ntoabuf[MAX_IPSTRLEN];

    if (domain && !client_address.IsAnyAddr())
        snprintf(buf, SQUIDHOSTNAMELEN * 3 + 10, "%s:%d-%s/%s", host, (int) port, client_address.NtoA(ntoabuf,MAX_IPSTRLEN), domain);
    else if (domain && client_address.IsAnyAddr())
        snprintf(buf, SQUIDHOSTNAMELEN * 3 + 10, "%s:%d/%s", host, (int) port, domain);
    else if ((!domain) && !client_address.IsAnyAddr())
        snprintf(buf, SQUIDHOSTNAMELEN * 3 + 10, "%s:%d-%s", host, (int) port, client_address.NtoA(ntoabuf,MAX_IPSTRLEN));
    else
        snprintf(buf, SQUIDHOSTNAMELEN * 3 + 10, "%s:%d", host, (int) port);

    debugs(48,6,"PconnPool::key(" << (host?host:"(no host!)") << "," << port << "," << (domain?domain:"(no domain)") << "," << client_address << "is {" << buf << "}" );
    return buf;
}