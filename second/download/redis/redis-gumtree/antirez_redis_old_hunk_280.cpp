        count = 5000000;
    }

    start = timeInMilliseconds();
    for (j = 0; j < count; j++) {
        int retval = dictAdd(dict,sdsfromlonglong(j),(void*)j);
        assert(retval == DICT_OK);
    }
    elapsed = timeInMilliseconds()-start;
    printf("Inserting 5M items: %lld ms\n", elapsed);
    assert((long)dictSize(dict) == count);
}
#endif
