int
ntlm_validate_packet(const ntlmhdr * hdr, const int32_t type)
{
    /*
     * Must be the correct security package and request type.
     * The 8 bytes compared includes the ASCII 'NUL'.
     */
    if (memcmp(hdr->signature, "NTLMSSP", 8) != 0) {
        fprintf(stderr, "ntlmCheckHeader: bad header signature\n");
        return NTLM_ERR_BLOB;
    }
    if (type == NTLM_ANY)
        return NTLM_ERR_NONE;

    if ((int32_t)le32toh(hdr->type) != type) {
        /* don't report this error - it's ok as we do a if() around this function */
        debug("ntlm_validate_packet: type is %d, wanted %d\n", le32toh(hdr->type), type);
        return NTLM_ERR_PROTOCOL;
    }
    return NTLM_ERR_NONE;
}