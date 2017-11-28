void addTargetAtTail(HttpHdrScTarget *t) {
        dlinkAddTail (t, &t->node, &targets);
    }