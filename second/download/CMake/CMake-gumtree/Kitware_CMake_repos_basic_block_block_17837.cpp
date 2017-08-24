{
    struct XXH_state32_t * state = (struct XXH_state32_t *) state_in;
    const BYTE* p = (const BYTE*)input;
    const BYTE* const bEnd = p + len;

#ifdef XXH_ACCEPT_NULL_INPUT_POINTER
    if (input==NULL) return XXH_ERROR;
#endif

    state->total_len += len;

    if (state->memsize + len < 16)   /* fill in tmp buffer */
    {
        XXH_memcpy(state->memory + state->memsize, input, len);
        state->memsize +=  len;
        return XXH_OK;
    }

    if (state->memsize)   /* some data left from previous update */
    {
        XXH_memcpy(state->memory + state->memsize, input, 16-state->memsize);
        {
            const U32* p32 = (const U32*)state->memory;
            state->v1 += XXH_readLE32(p32, endian) * PRIME32_2; state->v1 = XXH_rotl32(state->v1, 13); state->v1 *= PRIME32_1; p32++;
            state->v2 += XXH_readLE32(p32, endian) * PRIME32_2; state->v2 = XXH_rotl32(state->v2, 13); state->v2 *= PRIME32_1; p32++;
            state->v3 += XXH_readLE32(p32, endian) * PRIME32_2; state->v3 = XXH_rotl32(state->v3, 13); state->v3 *= PRIME32_1; p32++;
            state->v4 += XXH_readLE32(p32, endian) * PRIME32_2; state->v4 = XXH_rotl32(state->v4, 13); state->v4 *= PRIME32_1; p32++;
        }
        p += 16-state->memsize;
        state->memsize = 0;
    }

    if (p <= bEnd-16)
    {
        const BYTE* const limit = bEnd - 16;
        U32 v1 = state->v1;
        U32 v2 = state->v2;
        U32 v3 = state->v3;
        U32 v4 = state->v4;

        do
        {
            v1 += XXH_readLE32((const U32*)p, endian) * PRIME32_2; v1 = XXH_rotl32(v1, 13); v1 *= PRIME32_1; p+=4;
            v2 += XXH_readLE32((const U32*)p, endian) * PRIME32_2; v2 = XXH_rotl32(v2, 13); v2 *= PRIME32_1; p+=4;
            v3 += XXH_readLE32((const U32*)p, endian) * PRIME32_2; v3 = XXH_rotl32(v3, 13); v3 *= PRIME32_1; p+=4;
            v4 += XXH_readLE32((const U32*)p, endian) * PRIME32_2; v4 = XXH_rotl32(v4, 13); v4 *= PRIME32_1; p+=4;
        } while (p<=limit);

        state->v1 = v1;
        state->v2 = v2;
        state->v3 = v3;
        state->v4 = v4;
    }

    if (p < bEnd)
    {
        XXH_memcpy(state->memory, p, bEnd-p);
        state->memsize = (int)(bEnd-p);
    }

    return XXH_OK;
}