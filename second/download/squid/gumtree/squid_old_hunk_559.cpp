
    if (type == LFT_NONE) {
        fatalf("Can't parse configuration token: '%s'\n", def);
    }

    if (*cur == ' ') {
        space = 1;
        ++cur;
    }

done:

    switch (type) {
