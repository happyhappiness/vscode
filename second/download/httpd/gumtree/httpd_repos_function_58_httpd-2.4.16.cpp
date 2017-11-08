static apr_size_t round_up(apr_size_t val, apr_off_t round) {
    if (round > 1) {
        return (apr_size_t)(((val + round - 1) / round) * round);
    }
    return val;
}