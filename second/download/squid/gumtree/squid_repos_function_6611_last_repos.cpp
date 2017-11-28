int
Icmp::CheckSum(unsigned short *ptr, int size)
{
    long sum;
    unsigned short oddbyte;
    unsigned short answer;

    if (!ptr) return (int)htons(0xffff); // bad input.

    sum = 0;

    while (size > 1) {
        sum += *ptr;
        ++ptr;
        size -= 2;
    }

    if (size == 1) {
        oddbyte = 0;
        *((unsigned char *) &oddbyte) = *(unsigned char *) ptr;
        sum += oddbyte;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer = (unsigned short) ~sum;
    return (answer);
}