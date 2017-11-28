virtual void endingShutdown() override {
        debugs(29, 5, "Clearing Auth credentials cache: " << name);
        whichCache->reset();
    }