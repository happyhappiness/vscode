bool swap_if(const Value comparand, const Value replacement)
    { assert(Enabled()); return value == comparand ? value = replacement, true : false; }