{
        const BYTE* const limit = bEnd - 16;
        U32 v1 = seed + PRIME32_1 + PRIME32_2;
        U32 v2 = seed + PRIME32_2;
        U32 v3 = seed + 0;
        U32 v4 = seed - PRIME32_1;

        do
        {
            v1 += XXH_get32bits(p) * PRIME32_2; v1 = XXH_rotl32(v1, 13); v1 *= PRIME32_1; p+=4;
            v2 += XXH_get32bits(p) * PRIME32_2; v2 = XXH_rotl32(v2, 13); v2 *= PRIME32_1; p+=4;
            v3 += XXH_get32bits(p) * PRIME32_2; v3 = XXH_rotl32(v3, 13); v3 *= PRIME32_1; p+=4;
            v4 += XXH_get32bits(p) * PRIME32_2; v4 = XXH_rotl32(v4, 13); v4 *= PRIME32_1; p+=4;
        } while (p<=limit);

        h32 = XXH_rotl32(v1, 1) + XXH_rotl32(v2, 7) + XXH_rotl32(v3, 12) + XXH_rotl32(v4, 18);
    }