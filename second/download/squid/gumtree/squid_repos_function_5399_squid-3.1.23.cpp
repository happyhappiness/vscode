virtual esiProcessResult_t process (int dovars) {
        debugs(86,5, "esiProcessComplete: Processed " << this);
        return ESI_PROCESS_COMPLETE;
    }