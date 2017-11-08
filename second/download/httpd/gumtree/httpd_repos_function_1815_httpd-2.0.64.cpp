static APR_INLINE unsigned hash_addr(struct apr_sockaddr_t *sa)
{
    unsigned key;

    /* The key is the last four bytes of the IP address.
     * For IPv4, this is the entire address, as always.
     * For IPv6, this is usually part of the MAC address.
     */
    key = *(unsigned *)((char *)sa->ipaddr_ptr + sa->ipaddr_len - 4);
    return hash_inaddr(key);
}