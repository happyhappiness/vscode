void get_sid_string(char *buf, int blen, apr_uid_t id)
{
    PSID_IDENTIFIER_AUTHORITY psia;
    DWORD nsa;
    DWORD sa;
    int slen;

    /* Determine authority values (these is a big-endian value, 
     * and NT records the value as hex if the value is > 2^32.)
     */
    psia = GetSidIdentifierAuthority(id);
    nsa =  (DWORD)(psia->Value[5])        + ((DWORD)(psia->Value[4]) <<  8)
        + ((DWORD)(psia->Value[3]) << 16) + ((DWORD)(psia->Value[2]) << 24);
    sa  =  (DWORD)(psia->Value[1])        + ((DWORD)(psia->Value[0]) <<  8);
    if (sa) {
        slen = apr_snprintf(buf, blen, "S-%lu-0x%04x%08x",
                            SID_REVISION, sa, nsa);
    } else {
        slen = apr_snprintf(buf, blen, "S-%lu-%lu",
                            SID_REVISION, nsa);
    }

    /* Now append all the subauthority strings.
     */
    nsa = *GetSidSubAuthorityCount(id);
    for (sa = 0; sa < nsa; ++sa) {
        slen += apr_snprintf(buf + slen, blen - slen, "-%lu",
                             *GetSidSubAuthority(id, sa));
    }
}