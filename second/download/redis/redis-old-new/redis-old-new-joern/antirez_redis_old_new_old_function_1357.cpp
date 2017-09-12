int quicklistTest(int argc, char *argv[]) {
    unsigned int err = 0;

    UNUSED(argc);
    UNUSED(argv);

    TEST("create list") {
        quicklist *ql = quicklistCreate();
        ql_verify(ql, 0, 0, 0, 0);
        quicklistRelease(ql);
    }

    TEST("add to tail of empty list") {
        quicklist *ql = quicklistCreate();
        quicklistPushTail(ql, F, "hello", 6);
        /* 1 for head and 1 for tail beacuse 1 node = head = tail */
        ql_verify(ql, 1, 1, 1, 1);
        quicklistRelease(ql);
    }

    TEST("add to head of empty list") {
        quicklist *ql = quicklistCreate();
        quicklistPushHead(ql, F, "hello", 6);
        /* 1 for head and 1 for tail beacuse 1 node = head = tail */
        ql_verify(ql, 1, 1, 1, 1);
        quicklistRelease(ql);
    }

    for (size_t f = 0; f < 32; f++) {
        TEST_DESC("add to tail 5x at fill %lu", f) {
            quicklist *ql = quicklistCreate();
            for (int i = 0; i < 5; i++)
                quicklistPushTail(ql, f, genstr("hello", i), 32);
            if (ql->count != 5)
                ERROR;
            if (f == 32)
                ql_verify(ql, 1, 5, 5, 5);
            quicklistRelease(ql);
        }
    }

    for (size_t f = 0; f < 32; f++) {
        TEST_DESC("add to head 5x at fill %lu", f) {
            quicklist *ql = quicklistCreate();
            for (int i = 0; i < 5; i++)
                quicklistPushHead(ql, f, genstr("hello", i), 32);
            if (ql->count != 5)
                ERROR;
            if (f == 32)
                ql_verify(ql, 1, 5, 5, 5);
            quicklistRelease(ql);
        }
    }

    for (size_t f = 0; f < 512; f++) {
        TEST_DESC("add to tail 500x at fill %lu", f) {
            quicklist *ql = quicklistCreate();
            for (int i = 0; i < 500; i++)
                quicklistPushTail(ql, f, genstr("hello", i), 32);
            if (ql->count != 500)
                ERROR;
            if (f == 32)
                ql_verify(ql, 16, 500, 32, 20);
            quicklistRelease(ql);
        }
    }

    for (size_t f = 0; f < 512; f++) {
        TEST_DESC("add to head 500x at fill %lu", f) {
            quicklist *ql = quicklistCreate();
            for (int i = 0; i < 500; i++)
                quicklistPushHead(ql, f, genstr("hello", i), 32);
            if (ql->count != 500)
                ERROR;
            if (f == 32)
                ql_verify(ql, 16, 500, 20, 32);
            quicklistRelease(ql);
        }
    }

    TEST("rotate empty") {
        quicklist *ql = quicklistCreate();
        quicklistRotate(ql, F);
        ql_verify(ql, 0, 0, 0, 0);
        quicklistRelease(ql);
    }

    for (size_t f = 0; f < 32; f++) {
        TEST("rotate one val once") {
            quicklist *ql = quicklistCreate();
            quicklistPushHead(ql, F, "hello", 6);
            quicklistRotate(ql, F);
            ql_verify(ql, 1, 1, 1, 1);
            quicklistRelease(ql);
        }
    }

    for (size_t f = 0; f < 1024; f++) {
        TEST_DESC("rotate 500 val 5000 times at fill %lu", f) {
            quicklist *ql = quicklistCreate();
            quicklistPushHead(ql, f, "900", 3);
            quicklistPushHead(ql, f, "7000", 4);
            quicklistPushHead(ql, f, "-1200", 5);
            quicklistPushHead(ql, f, "42", 2);
            for (int i = 0; i < 500; i++)
                quicklistPushHead(ql, f, genstr("hello", i), 32);
            ql_info(ql);
            for (int i = 0; i < 5000; i++) {
                ql_info(ql);
                quicklistRotate(ql, f);
            }
            if (f == 1)
                ql_verify(ql, 504, 504, 1, 1);
            else if (f == 2)
                ql_verify(ql, 252, 504, 2, 2);
            else if (f == 32)
                ql_verify(ql, 16, 504, 32, 24);
            quicklistRelease(ql);
        }
    }

    TEST("pop empty") {
        quicklist *ql = quicklistCreate();
        quicklistPop(ql, QUICKLIST_HEAD, NULL, NULL, NULL);
        ql_verify(ql, 0, 0, 0, 0);
        quicklistRelease(ql);
    }

    TEST("pop 1 string from 1") {
        quicklist *ql = quicklistCreate();
        quicklistPushHead(ql, F, genstr("hello", 331), 32);
        unsigned char *data;
        unsigned int sz;
        long long lv;
        ql_info(ql);
        quicklistPop(ql, QUICKLIST_HEAD, &data, &sz, &lv);
        assert(data != NULL);
        assert(sz == 32);
        zfree(data);
        ql_verify(ql, 0, 0, 0, 0);
        quicklistRelease(ql);
    }

    TEST("pop head 1 number from 1") {
        quicklist *ql = quicklistCreate();
        quicklistPushHead(ql, F, "55513", 5);
        unsigned char *data;
        unsigned int sz;
        long long lv;
        ql_info(ql);
        quicklistPop(ql, QUICKLIST_HEAD, &data, &sz, &lv);
        assert(data == NULL);
        assert(lv == 55513);
        ql_verify(ql, 0, 0, 0, 0);
        quicklistRelease(ql);
    }

    TEST("pop head 500 from 500") {
        quicklist *ql = quicklistCreate();
        for (int i = 0; i < 500; i++)
            quicklistPushHead(ql, F, genstr("hello", i), 32);
        ql_info(ql);
        for (int i = 0; i < 500; i++) {
            unsigned char *data;
            unsigned int sz;
            long long lv;
            int ret = quicklistPop(ql, QUICKLIST_HEAD, &data, &sz, &lv);
            assert(ret == 1);
            assert(data != NULL);
            assert(sz == 32);
            zfree(data);
        }
        ql_verify(ql, 0, 0, 0, 0);
        quicklistRelease(ql);
    }

    TEST("pop head 5000 from 500") {
        quicklist *ql = quicklistCreate();
        for (int i = 0; i < 500; i++)
            quicklistPushHead(ql, F, genstr("hello", i), 32);
        for (int i = 0; i < 5000; i++) {
            unsigned char *data;
            unsigned int sz;
            long long lv;
            int ret = quicklistPop(ql, QUICKLIST_HEAD, &data, &sz, &lv);
            if (i < 500) {
                assert(ret == 1);
                assert(data != NULL);
                assert(sz == 32);
                zfree(data);
            } else {
                assert(ret == 0);
            }
        }
        ql_verify(ql, 0, 0, 0, 0);
        quicklistRelease(ql);
    }

    TEST("iterate forward over 500 list") {
        quicklist *ql = quicklistCreate();
        for (int i = 0; i < 500; i++)
            quicklistPushHead(ql, F, genstr("hello", i), 32);
        quicklistIter *iter = quicklistGetIterator(ql, AL_START_HEAD);
        quicklistEntry entry;
        int i = 499, count = 0;
        while (quicklistNext(iter, &entry)) {
            char *h = genstr("hello", i);
            if (strcmp((char *)entry.value, h))
                ERR("value [%s] didn't match [%s] at position %d", entry.value,
                    h, i);
            i--;
            count++;
        }
        if (count != 500)
            ERR("Didn't iterate over exactly 500 elements (%d)", i);
        ql_verify(ql, 16, 500, 20, 32);
        quicklistReleaseIterator(iter);
        quicklistRelease(ql);
    }

    TEST("iterate reverse over 500 list") {
        quicklist *ql = quicklistCreate();
        for (int i = 0; i < 500; i++)
            quicklistPushHead(ql, F, genstr("hello", i), 32);
        quicklistIter *iter = quicklistGetIterator(ql, AL_START_TAIL);
        quicklistEntry entry;
        int i = 0;
        while (quicklistNext(iter, &entry)) {
            char *h = genstr("hello", i);
            if (strcmp((char *)entry.value, h))
                ERR("value [%s] didn't match [%s] at position %d", entry.value,
                    h, i);
            i++;
        }
        if (i != 500)
            ERR("Didn't iterate over exactly 500 elements (%d)", i);
        ql_verify(ql, 16, 500, 20, 32);
        quicklistReleaseIterator(iter);
        quicklistRelease(ql);
    }

    TEST("insert before with 0 elements") {
        quicklist *ql = quicklistCreate();
        quicklistEntry entry;
        quicklistIndex(ql, 0, &entry);
        quicklistInsertBefore(ql, F, &entry, "abc", 4);
        ql_verify(ql, 1, 1, 1, 1);
        quicklistRelease(ql);
    }

    TEST("insert after with 0 elements") {
        quicklist *ql = quicklistCreate();
        quicklistEntry entry;
        quicklistIndex(ql, 0, &entry);
        quicklistInsertAfter(ql, F, &entry, "abc", 4);
        ql_verify(ql, 1, 1, 1, 1);
        quicklistRelease(ql);
    }

    TEST("insert after 1 element") {
        quicklist *ql = quicklistCreate();
        quicklistPushHead(ql, F, "hello", 6);
        quicklistEntry entry;
        quicklistIndex(ql, 0, &entry);
        quicklistInsertAfter(ql, F, &entry, "abc", 4);
        ql_verify(ql, 1, 2, 2, 2);
        quicklistRelease(ql);
    }

    TEST("insert before 1 element") {
        quicklist *ql = quicklistCreate();
        quicklistPushHead(ql, F, "hello", 6);
        quicklistEntry entry;
        quicklistIndex(ql, 0, &entry);
        quicklistInsertAfter(ql, F, &entry, "abc", 4);
        ql_verify(ql, 1, 2, 2, 2);
        quicklistRelease(ql);
    }

    for (size_t f = 0; f < 12; f++) {
        TEST_DESC("insert once in elements while iterating at fill %lu\n", f) {
            quicklist *ql = quicklistCreate();
            quicklistPushTail(ql, f, "abc", 3);
            quicklistPushTail(ql, 1, "def", 3); /* force to unique node */
            quicklistPushTail(ql, f, "bob", 3); /* force to reset for +3 */
            quicklistPushTail(ql, f, "foo", 3);
            quicklistPushTail(ql, f, "zoo", 3);

            itrprintr(ql, 1);
            /* insert "bar" before "bob" while iterating over list. */
            quicklistIter *iter = quicklistGetIterator(ql, AL_START_HEAD);
            quicklistEntry entry;
            while (quicklistNext(iter, &entry)) {
                if (!strncmp((char *)entry.value, "bob", 3)) {
                    /* Insert as fill = 1 so it spills into new node. */
                    quicklistInsertBefore(ql, f, &entry, "bar", 3);
                    /* NOTE! You can't continue iterating after an insert into
                     * the list.  You *must* re-create your iterator again if
                     * you want to traverse all entires. */
                    break;
                }
            }
            itrprintr(ql, 1);

            /* verify results */
            quicklistIndex(ql, 0, &entry);
            if (strncmp((char *)entry.value, "abc", 3))
                ERR("Value 0 didn't match, instead got: %.*s", entry.sz,
                    entry.value);
            quicklistIndex(ql, 1, &entry);
            if (strncmp((char *)entry.value, "def", 3))
                ERR("Value 1 didn't match, instead got: %.*s", entry.sz,
                    entry.value);
            quicklistIndex(ql, 2, &entry);
            if (strncmp((char *)entry.value, "bar", 3))
                ERR("Value 2 didn't match, instead got: %.*s", entry.sz,
                    entry.value);
            quicklistIndex(ql, 3, &entry);
            if (strncmp((char *)entry.value, "bob", 3))
                ERR("Value 3 didn't match, instead got: %.*s", entry.sz,
                    entry.value);
            quicklistIndex(ql, 4, &entry);
            if (strncmp((char *)entry.value, "foo", 3))
                ERR("Value 4 didn't match, instead got: %.*s", entry.sz,
                    entry.value);
            quicklistIndex(ql, 5, &entry);
            if (strncmp((char *)entry.value, "zoo", 3))
                ERR("Value 5 didn't match, instead got: %.*s", entry.sz,
                    entry.value);
            quicklistReleaseIterator(iter);
            quicklistRelease(ql);
        }
    }

    for (size_t f = 0; f < 1024; f++) {
        TEST_DESC("insert [before] 250 new in middle of 500 elements at fill"
                  " %ld",
                  f) {
            quicklist *ql = quicklistCreate();
            for (int i = 0; i < 500; i++)
                quicklistPushTail(ql, f, genstr("hello", i), 32);
            for (int i = 0; i < 250; i++) {
                quicklistEntry entry;
                quicklistIndex(ql, 250, &entry);
                quicklistInsertBefore(ql, f, &entry, genstr("abc", i), 32);
            }
            if (f == 32)
                ql_verify(ql, 25, 750, 32, 20);
            quicklistRelease(ql);
        }
    }

    for (size_t f = 0; f < 1024; f++) {
        TEST_DESC(
            "insert [after] 250 new in middle of 500 elements at fill %ld", f) {
            quicklist *ql = quicklistCreate();
            for (int i = 0; i < 500; i++)
                quicklistPushHead(ql, f, genstr("hello", i), 32);
            for (int i = 0; i < 250; i++) {
                quicklistEntry entry;
                quicklistIndex(ql, 250, &entry);
                quicklistInsertAfter(ql, f, &entry, genstr("abc", i), 32);
            }

            if (ql->count != 750)
                ERR("List size not 750, but rather %ld", ql->count);

            if (f == 32)
                ql_verify(ql, 26, 750, 20, 32);
            quicklistRelease(ql);
        }
    }

    TEST("duplicate empty list") {
        quicklist *ql = quicklistCreate();
        ql_verify(ql, 0, 0, 0, 0);
        quicklist *copy = quicklistDup(ql);
        ql_verify(copy, 0, 0, 0, 0);
        quicklistRelease(ql);
        quicklistRelease(copy);
    }

    TEST("duplicate list of 1 element") {
        quicklist *ql = quicklistCreate();
        quicklistPushHead(ql, F, genstr("hello", 3), 32);
        ql_verify(ql, 1, 1, 1, 1);
        quicklist *copy = quicklistDup(ql);
        ql_verify(copy, 1, 1, 1, 1);
        quicklistRelease(ql);
        quicklistRelease(copy);
    }

    TEST("duplicate list of 500") {
        quicklist *ql = quicklistCreate();
        for (int i = 0; i < 500; i++)
            quicklistPushHead(ql, F, genstr("hello", i), 32);
        ql_verify(ql, 16, 500, 20, 32);

        quicklist *copy = quicklistDup(ql);
        ql_verify(copy, 16, 500, 20, 32);
        quicklistRelease(ql);
        quicklistRelease(copy);
    }

    for (size_t f = 0; f < 512; f++) {
        TEST_DESC("index 1,200 from 500 list at fill %lu", f) {
            quicklist *ql = quicklistCreate();
            for (int i = 0; i < 500; i++)
                quicklistPushTail(ql, f, genstr("hello", i + 1), 32);
            quicklistEntry entry;
            quicklistIndex(ql, 1, &entry);
            if (!strcmp((char *)entry.value, "hello2"))
                OK;
            else
                ERR("Value: %s", entry.value);
            quicklistIndex(ql, 200, &entry);
            if (!strcmp((char *)entry.value, "hello201"))
                OK;
            else
                ERR("Value: %s", entry.value);
            quicklistRelease(ql);
        }

        TEST_DESC("index -1,-2 from 500 list at fill %lu", f) {
            quicklist *ql = quicklistCreate();
            for (int i = 0; i < 500; i++)
                quicklistPushTail(ql, f, genstr("hello", i + 1), 32);
            quicklistEntry entry;
            quicklistIndex(ql, -1, &entry);
            if (!strcmp((char *)entry.value, "hello500"))
                OK;
            else
                ERR("Value: %s", entry.value);
            quicklistIndex(ql, -2, &entry);
            if (!strcmp((char *)entry.value, "hello499"))
                OK;
            else
                ERR("Value: %s", entry.value);
            quicklistRelease(ql);
        }

        TEST_DESC("index -100 from 500 list at fill %lu", f) {
            quicklist *ql = quicklistCreate();
            for (int i = 0; i < 500; i++)
                quicklistPushTail(ql, f, genstr("hello", i + 1), 32);
            quicklistEntry entry;
            quicklistIndex(ql, -100, &entry);
            if (!strcmp((char *)entry.value, "hello401"))
                OK;
            else
                ERR("Value: %s", entry.value);
            quicklistRelease(ql);
        }

        TEST_DESC("index too big +1 from 50 list at fill %lu", f) {
            quicklist *ql = quicklistCreate();
            for (int i = 0; i < 50; i++)
                quicklistPushTail(ql, f, genstr("hello", i + 1), 32);
            quicklistEntry entry;
            if (quicklistIndex(ql, 50, &entry))
                ERR("Index found at 50 with 50 list: %.*s", entry.sz,
                    entry.value);
            else
                OK;
            quicklistRelease(ql);
        }
    }

    TEST("delete range empty list") {
        quicklist *ql = quicklistCreate();
        quicklistDelRange(ql, 5, 20);
        ql_verify(ql, 0, 0, 0, 0);
        quicklistRelease(ql);
    }

    TEST("delete range of entire node in list of one node") {
        quicklist *ql = quicklistCreate();
        for (int i = 0; i < 32; i++)
            quicklistPushHead(ql, F, genstr("hello", i), 32);
        ql_verify(ql, 1, 32, 32, 32);
        quicklistDelRange(ql, 0, 32);
        ql_verify(ql, 0, 0, 0, 0);
        quicklistRelease(ql);
    }

    TEST("delete range of entire node with overflow counts") {
        quicklist *ql = quicklistCreate();
        for (int i = 0; i < 32; i++)
            quicklistPushHead(ql, F, genstr("hello", i), 32);
        ql_verify(ql, 1, 32, 32, 32);
        quicklistDelRange(ql, 0, 128);
        ql_verify(ql, 0, 0, 0, 0);
        quicklistRelease(ql);
    }

    TEST("delete middle 100 of 500 list") {
        quicklist *ql = quicklistCreate();
        for (int i = 0; i < 500; i++)
            quicklistPushTail(ql, F, genstr("hello", i + 1), 32);
        ql_verify(ql, 16, 500, 32, 20);
        quicklistDelRange(ql, 200, 100);
        ql_verify(ql, 14, 400, 32, 20);
        quicklistRelease(ql);
    }

    TEST("delete negative 1 from 500 list") {
        quicklist *ql = quicklistCreate();
        for (int i = 0; i < 500; i++)
            quicklistPushTail(ql, F, genstr("hello", i + 1), 32);
        ql_verify(ql, 16, 500, 32, 20);
        quicklistDelRange(ql, -1, 1);
        ql_verify(ql, 16, 499, 32, 19);
        quicklistRelease(ql);
    }

    TEST("delete negative 1 from 500 list with overflow counts") {
        quicklist *ql = quicklistCreate();
        for (int i = 0; i < 500; i++)
            quicklistPushTail(ql, F, genstr("hello", i + 1), 32);
        ql_verify(ql, 16, 500, 32, 20);
        quicklistDelRange(ql, -1, 128);
        ql_verify(ql, 16, 499, 32, 19);
        quicklistRelease(ql);
    }

    TEST("delete negative 100 from 500 list") {
        quicklist *ql = quicklistCreate();
        for (int i = 0; i < 500; i++)
            quicklistPushTail(ql, F, genstr("hello", i + 1), 32);
        quicklistDelRange(ql, -100, 100);
        ql_verify(ql, 13, 400, 32, 16);
        quicklistRelease(ql);
    }

    TEST("delete -10 count 5 from 50 list") {
        quicklist *ql = quicklistCreate();
        for (int i = 0; i < 50; i++)
            quicklistPushTail(ql, F, genstr("hello", i + 1), 32);
        ql_verify(ql, 2, 50, 32, 18);
        quicklistDelRange(ql, -10, 5);
        ql_verify(ql, 2, 45, 32, 13);
        quicklistRelease(ql);
    }

    TEST("numbers only list read") {
        quicklist *ql = quicklistCreate();
        quicklistPushTail(ql, F, "1111", 4);
        quicklistPushTail(ql, F, "2222", 4);
        quicklistPushTail(ql, F, "3333", 4);
        quicklistPushTail(ql, F, "4444", 4);
        ql_verify(ql, 1, 4, 4, 4);
        quicklistEntry entry;
        quicklistIndex(ql, 0, &entry);
        if (entry.longval != 1111)
            ERR("Not 1111, %lld", entry.longval);
        quicklistIndex(ql, 1, &entry);
        if (entry.longval != 2222)
            ERR("Not 2222, %lld", entry.longval);
        quicklistIndex(ql, 2, &entry);
        if (entry.longval != 3333)
            ERR("Not 3333, %lld", entry.longval);
        quicklistIndex(ql, 3, &entry);
        if (entry.longval != 4444)
            ERR("Not 4444, %lld", entry.longval);
        if (quicklistIndex(ql, 4, &entry))
            ERR("Index past elements: %lld", entry.longval);
        quicklistIndex(ql, -1, &entry);
        if (entry.longval != 4444)
            ERR("Not 4444 (reverse), %lld", entry.longval);
        quicklistIndex(ql, -2, &entry);
        if (entry.longval != 3333)
            ERR("Not 3333 (reverse), %lld", entry.longval);
        quicklistIndex(ql, -3, &entry);
        if (entry.longval != 2222)
            ERR("Not 2222 (reverse), %lld", entry.longval);
        quicklistIndex(ql, -4, &entry);
        if (entry.longval != 1111)
            ERR("Not 1111 (reverse), %lld", entry.longval);
        if (quicklistIndex(ql, -5, &entry))
            ERR("Index past elements (reverse), %lld", entry.longval);
        quicklistRelease(ql);
    }

    TEST("numbers larger list read") {
        quicklist *ql = quicklistCreate();
        char num[32];
        long long nums[5000];
        for (int i = 0; i < 5000; i++) {
            nums[i] = -5157318210846258176 + i;
            int sz = ll2string(num, sizeof(num), nums[i]);
            quicklistPushTail(ql, F, num, sz);
        }
        quicklistPushTail(ql, F, "xxxxxxxxxxxxxxxxxxxx", 20);
        quicklistEntry entry;
        for (int i = 0; i < 5000; i++) {
            quicklistIndex(ql, i, &entry);
            if (entry.longval != nums[i])
                ERR("[%d] Not longval %lld but rather %lld", i, nums[i],
                    entry.longval);
            entry.longval = 0xdeadbeef;
        }
        quicklistIndex(ql, 5000, &entry);
        if (strncmp((char *)entry.value, "xxxxxxxxxxxxxxxxxxxx", 20))
            ERR("String val not match: %s", entry.value);
        ql_verify(ql, 157, 5001, 32, 9);
        quicklistRelease(ql);
    }

    TEST("numbers larger list read B") {
        quicklist *ql = quicklistCreate();
        quicklistPushTail(ql, F, "99", 2);
        quicklistPushTail(ql, F, "98", 2);
        quicklistPushTail(ql, F, "xxxxxxxxxxxxxxxxxxxx", 20);
        quicklistPushTail(ql, F, "96", 2);
        quicklistPushTail(ql, F, "95", 2);
        quicklistReplaceAtIndex(ql, 1, "foo", 3);
        quicklistReplaceAtIndex(ql, -1, "bar", 3);
        quicklistRelease(ql);
        OK;
    }

    for (size_t f = 0; f < 16; f++) {
        TEST_DESC("lrem test at fill %lu", f) {
            quicklist *ql = quicklistCreate();
            char *words[] = { "abc", "foo", "bar",  "foobar", "foobared",
                              "zap", "bar", "test", "foo" };
            char *result[] = { "abc", "foo",  "foobar", "foobared",
                               "zap", "test", "foo" };
            char *resultB[] = { "abc",      "foo", "foobar",
                                "foobared", "zap", "test" };
            for (int i = 0; i < 9; i++)
                quicklistPushTail(ql, f, words[i], strlen(words[i]));

            /* lrem 0 bar */
            quicklistIter *iter = quicklistGetIterator(ql, AL_START_HEAD);
            quicklistEntry entry;
            int i = 0;
            while (quicklistNext(iter, &entry)) {
                if (quicklistCompare(entry.zi, (unsigned char *)"bar", 3)) {
                    quicklistDelEntry(iter, &entry);
                }
                i++;
            }
            quicklistReleaseIterator(iter);

            /* check result of lrem 0 bar */
            iter = quicklistGetIterator(ql, AL_START_HEAD);
            i = 0;
            int ok = 1;
            while (quicklistNext(iter, &entry)) {
                /* Result must be: abc, foo, foobar, foobared, zap, test, foo */
                if (strncmp((char *)entry.value, result[i], entry.sz)) {
                    ERR("No match at position %d, got %.*s instead of %s", i,
                        entry.sz, entry.value, result[i]);
                    ok = 0;
                }
                i++;
            }
            quicklistReleaseIterator(iter);

            quicklistPushTail(ql, f, "foo", 3);

            /* lrem -2 foo */
            iter = quicklistGetIterator(ql, AL_START_TAIL);
            i = 0;
            int del = 2;
            while (quicklistNext(iter, &entry)) {
                if (quicklistCompare(entry.zi, (unsigned char *)"foo", 3)) {
                    quicklistDelEntry(iter, &entry);
                    del--;
                }
                if (!del)
                    break;
                i++;
            }
            quicklistReleaseIterator(iter);

            /* check result of lrem -2 foo */
            /* (we're ignoring the '2' part and still deleting all foo because
             * we only have two foo) */
            iter = quicklistGetIterator(ql, AL_START_TAIL);
            i = 0;
            size_t resB = sizeof(resultB) / sizeof(*resultB);
            while (quicklistNext(iter, &entry)) {
                /* Result must be: abc, foo, foobar, foobared, zap, test, foo */
                if (strncmp((char *)entry.value, resultB[resB - 1 - i],
                            entry.sz)) {
                    ERR("No match at position %d, got %.*s instead of %s", i,
                        entry.sz, entry.value, resultB[resB - 1 - i]);
                    ok = 0;
                }
                i++;
            }

            quicklistReleaseIterator(iter);
            /* final result of all tests */
            if (ok)
                OK;
            quicklistRelease(ql);
        }
    }

    for (size_t f = 0; f < 16; f++) {
        TEST_DESC("iterate reverse + delete at fill %lu", f) {
            quicklist *ql = quicklistCreate();
            quicklistPushTail(ql, f, "abc", 3);
            quicklistPushTail(ql, f, "def", 3);
            quicklistPushTail(ql, f, "hij", 3);
            quicklistPushTail(ql, f, "jkl", 3);
            quicklistPushTail(ql, f, "oop", 3);

            quicklistEntry entry;
            quicklistIter *iter = quicklistGetIterator(ql, AL_START_TAIL);
            int i = 0;
            while (quicklistNext(iter, &entry)) {
                if (quicklistCompare(entry.zi, (unsigned char *)"hij", 3)) {
                    quicklistDelEntry(iter, &entry);
                }
                i++;
            }
            quicklistReleaseIterator(iter);

            if (i != 5)
                ERR("Didn't iterate 5 times, iterated %d times.", i);

            /* Check results after deletion of "hij" */
            iter = quicklistGetIterator(ql, AL_START_HEAD);
            i = 0;
            char *vals[] = { "abc", "def", "jkl", "oop" };
            while (quicklistNext(iter, &entry)) {
                if (!quicklistCompare(entry.zi, (unsigned char *)vals[i], 3)) {
                    ERR("Value at %d didn't match %s\n", i, vals[i]);
                }
                i++;
            }
            quicklistReleaseIterator(iter);
            quicklistRelease(ql);
        }
    }

    for (size_t f = 0; f < 800; f++) {
        TEST_DESC("iterator at index test at fill %lu", f) {
            quicklist *ql = quicklistCreate();
            char num[32];
            long long nums[5000];
            for (int i = 0; i < 760; i++) {
                nums[i] = -5157318210846258176 + i;
                int sz = ll2string(num, sizeof(num), nums[i]);
                quicklistPushTail(ql, f, num, sz);
            }

            quicklistEntry entry;
            quicklistIter *iter =
                quicklistGetIteratorAtIdx(ql, AL_START_HEAD, 437);
            int i = 437;
            while (quicklistNext(iter, &entry)) {
                if (entry.longval != nums[i])
                    ERR("Expected %lld, but got %lld", entry.longval, nums[i]);
                i++;
            }
            quicklistReleaseIterator(iter);
            quicklistRelease(ql);
        }
    }

    for (size_t f = 0; f < 40; f++) {
        TEST_DESC("ltrim test A at fill %lu", f) {
            quicklist *ql = quicklistCreate();
            char num[32];
            long long nums[5000];
            for (int i = 0; i < 32; i++) {
                nums[i] = -5157318210846258176 + i;
                int sz = ll2string(num, sizeof(num), nums[i]);
                quicklistPushTail(ql, f, num, sz);
            }
            if (f == 32)
                ql_verify(ql, 1, 32, 32, 32);
            /* ltrim 25 53 (keep [25,32] inclusive = 7 remaining) */
            quicklistDelRange(ql, 0, 25);
            quicklistDelRange(ql, 0, 0);
            quicklistEntry entry;
            for (int i = 0; i < 7; i++) {
                quicklistIndex(ql, i, &entry);
                if (entry.longval != nums[25 + i])
                    ERR("Deleted invalid range!  Expected %lld but got %lld",
                        entry.longval, nums[25 + i]);
            }
            if (f == 32)
                ql_verify(ql, 1, 7, 7, 7);
            quicklistRelease(ql);
        }
    }

    for (size_t f = 0; f < 40; f++) {
        TEST_DESC("ltrim test B at fill %lu", f) {
            quicklist *ql = quicklistCreate();
            char num[32];
            long long nums[5000];
            for (int i = 0; i < 33; i++) {
                nums[i] = i;
                int sz = ll2string(num, sizeof(num), nums[i]);
                quicklistPushTail(ql, f, num, sz);
            }
            if (f == 32)
                ql_verify(ql, 2, 33, 32, 1);
            /* ltrim 5 16 (keep [5,16] inclusive = 12 remaining) */
            quicklistDelRange(ql, 0, 5);
            quicklistDelRange(ql, -16, 16);
            if (f == 32)
                ql_verify(ql, 1, 12, 12, 12);
            quicklistEntry entry;
            quicklistIndex(ql, 0, &entry);
            if (entry.longval != 5)
                ERR("A: longval not 5, but %lld", entry.longval);
            else
                OK;
            quicklistIndex(ql, -1, &entry);
            if (entry.longval != 16)
                ERR("B! got instead: %lld", entry.longval);
            else
                OK;
            quicklistPushTail(ql, f, "bobobob", 7);
            quicklistIndex(ql, -1, &entry);
            if (strncmp((char *)entry.value, "bobobob", 7))
                ERR("Tail doesn't match bobobob, it's %.*s instead", entry.sz,
                    entry.value);
            for (int i = 0; i < 12; i++) {
                quicklistIndex(ql, i, &entry);
                if (entry.longval != nums[5 + i])
                    ERR("Deleted invalid range!  Expected %lld but got %lld",
                        entry.longval, nums[5 + i]);
            }
            quicklistRelease(ql);
        }
    }

    for (size_t f = 0; f < 40; f++) {
        TEST_DESC("ltrim test C at fill %lu", f) {
            quicklist *ql = quicklistCreate();
            char num[32];
            long long nums[5000];
            for (int i = 0; i < 33; i++) {
                nums[i] = -5157318210846258176 + i;
                int sz = ll2string(num, sizeof(num), nums[i]);
                quicklistPushTail(ql, f, num, sz);
            }
            if (f == 32)
                ql_verify(ql, 2, 33, 32, 1);
            /* ltrim 3 3 (keep [3,3] inclusive = 1 remaining) */
            quicklistDelRange(ql, 0, 3);
            quicklistDelRange(ql, -29, 4000); /* make sure not loop forever */
            if (f == 32)
                ql_verify(ql, 1, 1, 1, 1);
            quicklistEntry entry;
            quicklistIndex(ql, 0, &entry);
            if (entry.longval != -5157318210846258173)
                ERROR;
            else
                OK;
            quicklistRelease(ql);
        }
    }

    for (size_t f = 0; f < 40; f++) {
        TEST_DESC("ltrim test D at fill %lu", f) {
            quicklist *ql = quicklistCreate();
            char num[32];
            long long nums[5000];
            for (int i = 0; i < 33; i++) {
                nums[i] = -5157318210846258176 + i;
                int sz = ll2string(num, sizeof(num), nums[i]);
                quicklistPushTail(ql, f, num, sz);
            }
            if (f == 32)
                ql_verify(ql, 2, 33, 32, 1);
            quicklistDelRange(ql, -12, 3);
            if (ql->count != 30)
                ERR("Didn't delete exactly three elements!  Count is: %lu",
                    ql->count);
            quicklistRelease(ql);
        }
    }

    for (size_t f = 0; f < 72; f++) {
        TEST_DESC("create quicklist from ziplist at fill %lu", f) {
            unsigned char *zl = ziplistNew();
            long long nums[32];
            char num[32];
            for (int i = 0; i < 33; i++) {
                nums[i] = -5157318210846258176 + i;
                int sz = ll2string(num, sizeof(num), nums[i]);
                zl = ziplistPush(zl, (unsigned char *)num, sz, ZIPLIST_TAIL);
            }
            for (int i = 0; i < 33; i++) {
                zl = ziplistPush(zl, (unsigned char *)genstr("hello", i), 32,
                                 ZIPLIST_TAIL);
            }
            quicklist *ql = quicklistCreateFromZiplist(f, zl);
            if (f == 1)
                ql_verify(ql, 66, 66, 1, 1);
            else if (f == 32)
                ql_verify(ql, 3, 66, 32, 2);
            else if (f == 66)
                ql_verify(ql, 1, 66, 66, 66);
            quicklistRelease(ql);
        }
    }

    if (!err)
        printf("ALL TESTS PASSED!\n");
    else
        ERR("Sorry, not all tests passed!  In fact, %d tests failed.", err);

    return err;
}