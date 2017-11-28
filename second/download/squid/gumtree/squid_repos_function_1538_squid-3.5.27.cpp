void
SwapChecksum24::set(uint32_t f1, uint32_t f2, uint32_t f3)
{
    uint64_t sum = f1;
    sum += f2;
    sum += f3;

    while (const uint64_t higherBits = sum >> 24)
        sum = (sum & 0xFFFFFF) + higherBits;

    sum = ~sum;

    raw[0] = static_cast<uint8_t>(sum);
    raw[1] = static_cast<uint8_t>(sum >> 8);
    raw[2] = static_cast<uint8_t>(sum >> 16);
}