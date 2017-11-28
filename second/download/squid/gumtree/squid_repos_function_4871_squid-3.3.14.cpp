bool canDial(AsyncCall &call) const {
        return cbdataReferenceValid(callback_data) && callback;
    }