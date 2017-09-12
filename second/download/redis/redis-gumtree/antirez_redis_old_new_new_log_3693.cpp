printf(
            "{"
                "addr 0x%08lx, "
                "index %2d, "
                "offset %5ld, "
                "rl: %5u, "
                "hs %2u, "
                "pl: %5u, "
                "pls: %2u, "
                "payload %5u"
            "} ",
            (long unsigned int)p,
            index,
            p-zl,
            entry.headersize+entry.len,
            entry.headersize,
            entry.prevrawlen,
            entry.prevrawlensize,
            entry.len);