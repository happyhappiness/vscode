Value fetchAndAnd(const Value v2)
    { assert(Enabled()); const Value v1 = value; value &= v2; return v1; }