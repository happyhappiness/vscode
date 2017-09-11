            unsigned int r = rand() & HLL_REGISTER_MAX;

            bytecounters[i] = r;
            HLL_SET_REGISTER(bitcounters,i,r);
        }
        /* Check that we are able to retrieve the same values. */
        for (i = 0; i < HLL_REGISTERS; i++) {
            unsigned int val;

            HLL_GET_REGISTER(val,bitcounters,i);
            if (val != bytecounters[i]) {
                addReplyErrorFormat(c,
                    "TESTFAILED Register %d should be %d but is %d",
