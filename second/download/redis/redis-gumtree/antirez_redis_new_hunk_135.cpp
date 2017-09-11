    while(*p != ZIP_END) {
        zipEntry(p, &entry);
        printf(
            "{\n"
                "\taddr 0x%08lx,\n"
                "\tindex %2d,\n"
                "\toffset %5ld,\n"
                "\thdr+entry len: %5u,\n"
                "\thdr len%2u,\n"
                "\tprevrawlen: %5u,\n"
                "\tprevrawlensize: %2u,\n"
                "\tpayload %5u\n",
            (long unsigned)p,
            index,
            (unsigned long) (p-zl),
