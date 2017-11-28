static Store &Root() {
        if (CurrentRoot == NULL)
            fatal("No Store Root has been set");
        return *CurrentRoot;
    }