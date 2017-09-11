    printf("Upgrade from int32 to int64: "); {
        is = intsetNew();
        is = intsetAdd(is,65535,NULL);
        assert(is->encoding == INTSET_ENC_INT32);
        is = intsetAdd(is,4294967295,NULL);
        assert(is->encoding == INTSET_ENC_INT64);
        assert(intsetFind(is,65535));
        assert(intsetFind(is,4294967295));
        checkConsistency(is);

        is = intsetNew();
        is = intsetAdd(is,65535,NULL);
        assert(is->encoding == INTSET_ENC_INT32);
        is = intsetAdd(is,-4294967295,NULL);
        assert(is->encoding == INTSET_ENC_INT64);
        assert(intsetFind(is,65535));
        assert(intsetFind(is,-4294967295));
        checkConsistency(is);
