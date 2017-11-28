int checkEvents(int timeout) {
        Store::Root().callback();
        return EVENT_IDLE;
    }