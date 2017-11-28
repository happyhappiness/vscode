void
ntlm_add_to_payload(const ntlmhdr *packet_hdr,
                    char *payload,
                    int *payload_length,
                    strhdr * hdr,
                    const char *toadd,
                    const uint16_t toadd_length)
{
    int l = (*payload_length);
    memcpy(payload + l, toadd, toadd_length);

    hdr->len = htole16(toadd_length);
    hdr->maxlen = htole16(toadd_length);
    const off_t o = l + reinterpret_cast<const ntlmhdr *>(payload) - packet_hdr;
    hdr->offset = htole32(o & 0xFFFFFFFF);
    (*payload_length) += toadd_length;
}