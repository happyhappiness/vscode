void setMask(http_hdr_sc_type id, bool newval) {
        if (newval) EBIT_SET(mask,id);
        else EBIT_CLR(mask,id);
    }