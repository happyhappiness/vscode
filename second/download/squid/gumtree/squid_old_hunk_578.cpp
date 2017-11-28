#include <string.h>
#endif
#if HAVE_ARPA_INET_H
/* for inet_ntoa() */
#include <arpa/inet.h>
#endif

/* Debugging only. Dump the address content when a fatal assert is encountered. */
#define IASSERT(a,b)  \
	if(!(b)){	printf("assert \"%s\" at line %d\n", a, __LINE__); \
		printf("Ip::Address invalid? with IsIPv4()=%c, IsIPv6()=%c\n",(IsIPv4()?'T':'F'),(IsIPv6()?'T':'F')); \
		printf("ADDRESS:"); \
		for(unsigned int i = 0; i < sizeof(m_SocketAddr.sin6_addr); ++i) { \
			printf(" %x", m_SocketAddr.sin6_addr.s6_addr[i]); \
		} printf("\n"); assert(b); \
	}

int
Ip::Address::GetCIDR() const
{
    uint8_t shift,byte;
    uint8_t bit,caught;
    int len = 0;
    const uint8_t *ptr= m_SocketAddr.sin6_addr.s6_addr;

    /* Let's scan all the bits from Most Significant to Least */
    /* Until we find an "0" bit. Then, we return */
    shift=0;

    /* return IPv4 CIDR for any Mapped address */
    /* Thus only check the mapped bit */

    if ( !IsIPv6() ) {
        shift = 12;
    }

    for (; shift<sizeof(m_SocketAddr.sin6_addr) ; ++shift) {
        byte= *(ptr+shift);

        if (byte == 0xFF) {
            len += 8;
            continue ;  /* A short-cut */
        }

        for (caught = 0 , bit= 7 ; !caught && (bit <= 7); --bit) {
            caught = ((byte & 0x80) == 0x00);  /* Found a '0' at 'bit' ? */

            if (!caught)
                ++len;

            byte <<= 1;
        }

        if (caught)
            break; /* We have found the most significant "0" bit.  */
    }

    return len;
}

int
Ip::Address::ApplyMask(Ip::Address const &mask_addr)
{
    uint32_t *p1 = (uint32_t*)(&m_SocketAddr.sin6_addr);
    uint32_t const *p2 = (uint32_t const *)(&mask_addr.m_SocketAddr.sin6_addr);
    unsigned int blen = sizeof(m_SocketAddr.sin6_addr)/sizeof(uint32_t);
    unsigned int changes = 0;

    for (unsigned int i = 0; i < blen; ++i) {
        if ((p1[i] & p2[i]) != p1[i])
            ++changes;

