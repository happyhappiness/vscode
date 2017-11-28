virtual Security::ContextPointer getTlsContext() {
        return icapService->sslContext;
    }