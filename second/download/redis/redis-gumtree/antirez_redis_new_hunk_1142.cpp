        minidx = 2; maxidx = 3;
    }

    if (zslParseRange(c->argv[minidx],c->argv[maxidx],&range) != C_OK) {
        addReplyError(c,"min or max is not a float");
        return;
    }
