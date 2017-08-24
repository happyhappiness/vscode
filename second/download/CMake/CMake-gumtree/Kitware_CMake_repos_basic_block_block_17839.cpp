{
        h32 += (*p) * PRIME32_5;
        h32 = XXH_rotl32(h32, 11) * PRIME32_1;
        p++;
    }