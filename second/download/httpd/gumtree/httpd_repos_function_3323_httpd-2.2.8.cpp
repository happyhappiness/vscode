void apr__SHA512_Transform(SHA512_CTX* context, const sha2_word64* data) {
        sha2_word64     a, b, c, d, e, f, g, h, s0, s1;
        sha2_word64     T1, *W512 = (sha2_word64*)context->buffer;
        int             j;

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
                ROUND512_0_TO_15(a,b,c,d,e,f,g,h);
                ROUND512_0_TO_15(h,a,b,c,d,e,f,g);
                ROUND512_0_TO_15(g,h,a,b,c,d,e,f);
                ROUND512_0_TO_15(f,g,h,a,b,c,d,e);
                ROUND512_0_TO_15(e,f,g,h,a,b,c,d);
                ROUND512_0_TO_15(d,e,f,g,h,a,b,c);
                ROUND512_0_TO_15(c,d,e,f,g,h,a,b);
                ROUND512_0_TO_15(b,c,d,e,f,g,h,a);
        } while (j < 16);

        /* Now for the remaining rounds up to 79: */
        do {
                ROUND512(a,b,c,d,e,f,g,h);
                ROUND512(h,a,b,c,d,e,f,g);
                ROUND512(g,h,a,b,c,d,e,f);
                ROUND512(f,g,h,a,b,c,d,e);
                ROUND512(e,f,g,h,a,b,c,d);
                ROUND512(d,e,f,g,h,a,b,c);
                ROUND512(c,d,e,f,g,h,a,b);
                ROUND512(b,c,d,e,f,g,h,a);
        } while (j < 80);

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