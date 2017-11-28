void maxAge(int v) {
        if (v >= 0) { //setting
            setMask(SC_MAX_AGE,true);
            max_age=v;
        } else {
            setMask(SC_MAX_AGE,false);
            max_age=MAX_AGE_UNSET;
        }
    }