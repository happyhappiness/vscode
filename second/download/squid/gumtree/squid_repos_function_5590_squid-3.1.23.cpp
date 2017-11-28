void
ntlm_add_to_payload(char *payload, int *payload_length,
                    strhdr * hdr, char *toadd,
                    int toadd_length, int base_offset)
{

    int l = (*payload_length);
    memcpy(payload + l, toadd, toadd_length);

    hdr->len = htole16(toadd_length);
    hdr->maxlen = htole16(toadd_length);
    hdr->offset = htole32(l + base_offset);	/* 48 is the base offset of the payload */
    (*payload_length) += toadd_length;
}