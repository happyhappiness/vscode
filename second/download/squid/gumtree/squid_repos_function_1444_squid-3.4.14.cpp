void
SwapChecksum24::set(int32_t f1, uint64_t f2)
{
    // split the second 64bit word into two 32bit words
    set(static_cast<uint32_t>(f1),
        static_cast<uint32_t>(f2 >> 32),
        static_cast<uint32_t>(f2 & 0xFFFFFFFF));
}