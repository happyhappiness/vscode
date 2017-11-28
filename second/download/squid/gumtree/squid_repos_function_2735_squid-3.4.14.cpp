bool clientExpectsConnectResponse() const {
        return !(request != NULL &&
                 (request->flags.interceptTproxy || request->flags.intercepted));
    }