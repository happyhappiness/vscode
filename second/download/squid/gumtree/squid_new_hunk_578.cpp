#include <string.h>
#endif
#if HAVE_ARPA_INET_H
/* for inet_ntoa() */
#include <arpa/inet.h>
#endif
#if HAVE_WS2TCPIP_H
// Windows IPv6 definitions
#include <ws2tcpip.h>
#endif

// some OS (ie WIndows) define IN6_ADDR_EQUAL instead
#if !defined(IN6_ARE_ADDR_EQUAL) && _SQUID_WINDOWS_
#define IN6_ARE_ADDR_EQUAL IN6_ADDR_EQUAL
#endif

/* Debugging only. Dump the address content when a fatal assert is encountered. */
#define IASSERT(a,b)  \
	if(!(b)){	printf("assert \"%s\" at line %d\n", a, __LINE__); \
		printf("Ip::Address invalid? with isIPv4()=%c, isIPv6()=%c\n",(isIPv4()?'T':'F'),(isIPv6()?'T':'F')); \
		printf("ADDRESS:"); \
		for(unsigned int i = 0; i < sizeof(mSocketAddr_.sin6_addr); ++i) { \
			printf(" %x", mSocketAddr_.sin6_addr.s6_addr[i]); \
		} printf("\n"); assert(b); \
	}

int
Ip::Address::cidr() const
{
    uint8_t shift,ipbyte;
    uint8_t bit,caught;
    int len = 0;
    const uint8_t *ptr= mSocketAddr_.sin6_addr.s6_addr;

    /* Let's scan all the bits from Most Significant to Least */
    /* Until we find an "0" bit. Then, we return */
    shift=0;

    /* return IPv4 CIDR for any Mapped address */
    /* Thus only check the mapped bit */

    if ( !isIPv6() ) {
        shift = 12;
    }

    for (; shift<sizeof(mSocketAddr_.sin6_addr) ; ++shift) {
        ipbyte= *(ptr+shift);

        if (ipbyte == 0xFF) {
            len += 8;
            continue ;  /* A short-cut */
        }

        for (caught = 0 , bit= 7 ; !caught && (bit <= 7); --bit) {
            caught = ((ipbyte & 0x80) == 0x00);  /* Found a '0' at 'bit' ? */

            if (!caught)
                ++len;

            ipbyte <<= 1;
        }

        if (caught)
            break; /* We have found the most significant "0" bit.  */
    }

    return len;
}

int
Ip::Address::applyMask(Ip::Address const &mask_addr)
{
    uint32_t *p1 = (uint32_t*)(&mSocketAddr_.sin6_addr);
    uint32_t const *p2 = (uint32_t const *)(&mask_addr.mSocketAddr_.sin6_addr);
    unsigned int blen = sizeof(mSocketAddr_.sin6_addr)/sizeof(uint32_t);
    unsigned int changes = 0;

    for (unsigned int i = 0; i < blen; ++i) {
        if ((p1[i] & p2[i]) != p1[i])
            ++changes;

