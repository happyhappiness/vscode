bool canDial(AsyncCall &) const {
        return cbdataReferenceValid(callback_data) && callback;
    }