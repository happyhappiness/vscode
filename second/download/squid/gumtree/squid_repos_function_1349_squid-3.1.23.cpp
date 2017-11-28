_icp_common_t *
_icp_common_t::createMessage(
    icp_opcode opcode,
    int flags,
    const char *url,
    int reqnum,
    int pad)
{
    char *buf = NULL;
    icp_common_t *headerp = NULL;
    char *urloffset = NULL;
    int buf_len;
    buf_len = sizeof(icp_common_t) + strlen(url) + 1;

    if (opcode == ICP_QUERY)
        buf_len += sizeof(u_int32_t);

    buf = (char *) xcalloc(buf_len, 1);

    headerp = (icp_common_t *) (void *) buf;

    headerp->opcode = (char) opcode;

    headerp->version = ICP_VERSION_CURRENT;

    headerp->length = (u_int16_t) htons(buf_len);

    headerp->reqnum = htonl(reqnum);

    headerp->flags = htonl(flags);

    headerp->pad = htonl(pad);

    theOutICPAddr.GetInAddr( *((struct in_addr*)&headerp->shostid) );

    urloffset = buf + sizeof(icp_common_t);

    if (opcode == ICP_QUERY)
        urloffset += sizeof(u_int32_t);

    xmemcpy(urloffset, url, strlen(url));

    return (icp_common_t *)buf;
}