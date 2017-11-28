int
ntlmCheckHeader(ntlmhdr * hdr, int type)
{
    /*
     * Must be the correct security package and request type. The
     * 8 bytes compared includes the ASCII 'NUL'.
     */
    if (memcmp(hdr->signature, "NTLMSSP", 8) != 0) {
        fprintf(stderr, "ntlmCheckHeader: bad header signature\n");
        return (-1);
    }
    if (type == NTLM_ANY)
        return 0;

    if (le32toh(hdr->type) != type) {
        /* don't report this error - it's ok as we do a if() around this function */
//      fprintf(stderr, "ntlmCheckHeader: type is %d, wanted %d\n",
        //          le32toh(hdr->type), type);
        return (-1);
    }
    return (0);
}