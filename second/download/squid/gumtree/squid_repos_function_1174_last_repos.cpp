int checkEvents(int) {
        Store::Root().callback();
        return EVENT_IDLE;
    }