    printf("Upgrade from int16 to int64: "); {
        is = intsetNew();
        is = intsetAdd(is,32,NULL);
        assert(is->encoding == INTSET_ENC_INT16);
        is = intsetAdd(is,4294967295,NULL);
        assert(is->encoding == INTSET_ENC_INT64);
        assert(intsetFind(is,32));
        assert(intsetFind(is,4294967295));
        checkConsistency(is);

        is = intsetNew();
        is = intsetAdd(is,32,NULL);
        assert(is->encoding == INTSET_ENC_INT16);
        is = intsetAdd(is,-4294967295,NULL);
        assert(is->encoding == INTSET_ENC_INT64);
        assert(intsetFind(is,32));
        assert(intsetFind(is,-4294967295));
        checkConsistency(is);
