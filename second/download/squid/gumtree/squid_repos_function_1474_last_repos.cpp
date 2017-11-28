StatHist &
StatHist::operator += (const StatHist &B)
{
    Must(capacity_ == B.capacity_);
    Must(min_ == B.min_);
    Must(max_ == B.max_);

    if (B.bins == NULL) { // B was not yet initializted
        return *this;
    }
    if (bins == NULL) { // this histogram was not yet initialized
        *this = B;
        return *this;
    }
    for (unsigned int i = 0; i < capacity_; ++i) {
        bins[i] += B.bins[i];
    }
    return *this;
}