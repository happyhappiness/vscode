bool includes (int anInt) const {
        if (anInt < _min || anInt > _max)
            return false;

        return true;
    }