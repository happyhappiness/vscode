virtual void syncConfig() override {
        debugs(29, 5, "Reconfiguring Auth credentials cache: " << name);
        whichCache->doConfigChangeCleanup();
    }