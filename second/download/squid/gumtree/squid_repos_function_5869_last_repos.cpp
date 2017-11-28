static void
random_vector(char *aVector)
{
    static std::mt19937 mt(time(0));
    static xuniform_int_distribution<uint8_t> dist;

    for (int i = 0; i < AUTH_VECTOR_LEN; ++i)
        aVector[i] = static_cast<char>(dist(mt) & 0xFF);
}