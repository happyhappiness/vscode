{
        XXH_memcpy(state->memory, p, bEnd-p);
        state->memsize = (int)(bEnd-p);
    }