static int
rfc1035NameUnpack(const char *buf, size_t sz, unsigned int *off, unsigned short *rdlength, char *name, size_t ns, int rdepth)
{
    unsigned int no = 0;
    unsigned char c;
    size_t len;
    assert(ns > 0);
    do {
        if ((*off) >= sz) {
            RFC1035_UNPACK_DEBUG;
            return 1;
        }
        c = *(buf + (*off));
        if (c > 191) {
            /* blasted compression */
            unsigned short s;
            unsigned int ptr;
            if (rdepth > 64) {  /* infinite pointer loop */
                RFC1035_UNPACK_DEBUG;
                return 1;
            }
            memcpy(&s, buf + (*off), sizeof(s));
            s = ntohs(s);
            (*off) += sizeof(s);
            /* Sanity check */
            if ((*off) > sz) {
                RFC1035_UNPACK_DEBUG;
                return 1;
            }
            ptr = s & 0x3FFF;
            /* Make sure the pointer is inside this message */
            if (ptr >= sz) {
                RFC1035_UNPACK_DEBUG;
                return 1;
            }
            return rfc1035NameUnpack(buf, sz, &ptr, rdlength, name + no, ns - no, rdepth + 1);
        } else if (c > RFC1035_MAXLABELSZ) {
            /*
             * "(The 10 and 01 combinations are reserved for future use.)"
             */
            RFC1035_UNPACK_DEBUG;
            return 1;
        } else {
            (*off)++;
            len = (size_t) c;
            if (len == 0)
                break;
            if (len > (ns - no - 1)) {  /* label won't fit */
                RFC1035_UNPACK_DEBUG;
                return 1;
            }
            if ((*off) + len >= sz) {   /* message is too short */
                RFC1035_UNPACK_DEBUG;
                return 1;
            }
            memcpy(name + no, buf + (*off), len);
            (*off) += len;
            no += len;
            *(name + (no++)) = '.';
            if (rdlength)
                *rdlength += len + 1;
        }
    } while (c > 0 && no < ns);
    if (no)
        *(name + no - 1) = '\0';
    else
        *name = '\0';
    /* make sure we didn't allow someone to overflow the name buffer */
    assert(no <= ns);
    return 0;
}