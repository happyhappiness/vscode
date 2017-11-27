static int
rfc1035NameUnpack(const char *buf, size_t sz, off_t * off, char *name, size_t ns
)
{
    off_t no = 0;
    unsigned char c;
    size_t len;
    static int loop_detect = 0;
    if (loop_detect > 2)
	return 4;		/* compression loop */
    if (ns <= 0)
	return 4;		/* probably compression loop */
    do {
	if ((*off) >= sz)
	    break;
	c = *(buf + (*off));
	if (c > 191) {
	    /* blasted compression */
	    int rc;
	    unsigned short s;
	    off_t ptr;
	    memcpy(&s, buf + (*off), sizeof(s));
	    s = ntohs(s);
	    (*off) += sizeof(s);
	    /* Sanity check */
	    if ((*off) >= sz)
		return 1;	/* message too short */
	    ptr = s & 0x3FFF;
	    /* Make sure the pointer is inside this message */
	    if (ptr >= sz)
		return 2;	/* bad compression ptr */
	    if (ptr < DNS_MSG_HDR_SZ)
		return 2;	/* bad compression ptr */
	    loop_detect++;
	    rc = rfc1035NameUnpack(buf, sz, &ptr, name + no, ns - no);
	    loop_detect--;
	    return rc;
	} else if (c > RFC1035_MAXLABELSZ) {
	    /*
	     * "(The 10 and 01 combinations are reserved for future use.)"
	     */
	    return 3;		/* reserved label/compression flags */
	    break;
	} else {
	    (*off)++;
	    len = (size_t) c;
	    if (len == 0)
		break;
	    if (len > (ns - 1))
		len = ns - 1;
	    if ((*off) + len > sz)
		return 4;	/* message is too short */
	    if (no + len + 1 > ns)
		return 5;	/* qname would overflow name buffer */
	    memcpy(name + no, buf + (*off), len);
	    (*off) += len;
	    no += len;
	    *(name + (no++)) = '.';
	}
    } while (c > 0);
    if (no > 0)
	*(name + no - 1) = '\0';
    /* make sure we didn't allow someone to overflow the name buffer */
    assert(no <= ns);
    return 0;
}