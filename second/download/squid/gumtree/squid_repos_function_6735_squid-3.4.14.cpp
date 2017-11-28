int
base64_encode_len(int len)
{
    // NP: some magic numbers + potential nil-terminator
    return ((len + 2) / 3 * 4) + 1;
}