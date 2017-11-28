void
eventAddIsh(const char *name, EVH * func, void *arg, double delta_ish, int weight)
{
    if (delta_ish >= 3.0) {
        // Default seed is fine. We just need values random enough
        // relative to each other to prevent waves of synchronised activity.
        static std::mt19937 rng;
        auto third = (delta_ish/3.0);
        xuniform_real_distribution<> thirdIsh(delta_ish - third, delta_ish + third);
        delta_ish = thirdIsh(rng);
    }

    eventAdd(name, func, arg, delta_ish, weight);
}