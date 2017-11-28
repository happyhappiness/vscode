void defaultTo(bool beSet) {
        Must(setHow_ != optConfigured);
        setHow_ = optImplicitly;
        option = beSet;
    }