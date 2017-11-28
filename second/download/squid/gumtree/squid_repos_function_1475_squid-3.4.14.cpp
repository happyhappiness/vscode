void addTarget(HttpHdrScTarget *t) {
        dlinkAdd(t, &t->node, &targets);
    }