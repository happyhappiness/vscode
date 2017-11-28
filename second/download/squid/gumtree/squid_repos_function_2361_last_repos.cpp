void Private(const String &v) {
        setMask(HttpHdrCcType::CC_PRIVATE,true);
        if (!v.size())
            return;
        // uses append for multi-line headers
        if (private_.size() > 0)
            private_.append(",");
        private_.append(v);
    }