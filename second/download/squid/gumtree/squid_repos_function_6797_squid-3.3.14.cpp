void
ntlm_add_to_payload(const ntlmhdr *packet_hdr,
                    char *payload,
                    int *payload_length,
                    strhdr * hdr,
                    const char *toadd,
                    const int toadd_length)
{
    int l = (*payload_length);
    memcpy(payload + l, toadd, toadd_length);

    hdr->len = htole16(toadd_length);
    hdr->maxlen = htole16(toadd_length);
    hdr->offset = htole32(l + payload - (char*)packet_hdr);
    (*payload_length) += toadd_length;
}