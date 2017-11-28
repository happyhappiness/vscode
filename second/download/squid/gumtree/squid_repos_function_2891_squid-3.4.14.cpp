void Private(String &v) {
        setMask(CC_PRIVATE,true);
        // uses append for multi-line headers
        if (private_.defined())
            private_.append(",");
        private_.append(v);
    }