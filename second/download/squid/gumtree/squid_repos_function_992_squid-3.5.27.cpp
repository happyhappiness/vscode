void reserveSpace(size_type minSpace) {
        Must(minSpace <= maxSize);
        Must(length() <= maxSize - minSpace);
        reserveCapacity(length()+minSpace);
    }