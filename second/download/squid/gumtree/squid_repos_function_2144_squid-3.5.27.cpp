void operator() (DelayTaggedBucket::Pointer const &current) {
        current->stats(sentry);
    }