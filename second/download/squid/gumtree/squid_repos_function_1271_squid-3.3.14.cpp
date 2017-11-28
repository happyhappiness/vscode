void
eventAddIsh(const char *name, EVH * func, void *arg, double delta_ish, int weight)
{
    if (delta_ish >= 3.0) {
        const double two_third = (2.0 * delta_ish) / 3.0;
        delta_ish = two_third + (drand48() * two_third);
        /*
         * I'm sure drand48() isn't portable.  Tell me what function
         * you have that returns a random double value in the range 0,1.
         */
    }

    eventAdd(name, func, arg, delta_ish, weight);
}