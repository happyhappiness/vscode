void apr__SHA256_Transform(SHA256_CTX* context, const sha2_word32* data) {
        sha2_word32     a, b, c, d, e, f, g, h, s0, s1;
        sha2_word32     T1, *W256;
        int             j;

        W256 = (sha2_word32*)context->buffer;

        /* Initialize registers with the prev. intermediate value */
        a = context->state[0];
        b = context->state[1];
        c = context->state[2];
        d = context->state[3];
        e = context->state[4];
        f = context->state[5];
        g = context->state[6];
        h = context->state[7];

        j = 0;
        do {
                /* Rounds 0 to 15 (unrolled): */
                ROUND256_0_TO_15(a,b,c,d,e,f,g,h);
                ROUND256_0_TO_15(h,a,b,c,d,e,f,g);
                ROUND256_0_TO_15(g,h,a,b,c,d,e,f);
                ROUND256_0_TO_15(f,g,h,a,b,c,d,e);
                ROUND256_0_TO_15(e,f,g,h,a,b,c,d);
                ROUND256_0_TO_15(d,e,f,g,h,a,b,c);
                ROUND256_0_TO_15(c,d,e,f,g,h,a,b);
                ROUND256_0_TO_15(b,c,d,e,f,g,h,a);
        } while (j < 16);

        /* Now for the remaining rounds to 64: */
        do {
                ROUND256(a,b,c,d,e,f,g,h);
                ROUND256(h,a,b,c,d,e,f,g);
                ROUND256(g,h,a,b,c,d,e,f);
                ROUND256(f,g,h,a,b,c,d,e);
                ROUND256(e,f,g,h,a,b,c,d);
                ROUND256(d,e,f,g,h,a,b,c);
                ROUND256(c,d,e,f,g,h,a,b);
                ROUND256(b,c,d,e,f,g,h,a);
        } while (j < 64);

        /* Compute the current intermediate hash value */
        context->state[0] += a;
        context->state[1] += b;
        context->state[2] += c;
        context->state[3] += d;
        context->state[4] += e;
        context->state[5] += f;
        context->state[6] += g;
        context->state[7] += h;

        /* Clean up */
        a = b = c = d = e = f = g = h = T1 = 0;
}