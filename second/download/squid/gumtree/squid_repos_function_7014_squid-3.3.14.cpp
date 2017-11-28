value_type pop() {
        if (!count)
            return value_type();

        value_type result = items[--count];

        this->items[count] = value_type();

        return result;
    }