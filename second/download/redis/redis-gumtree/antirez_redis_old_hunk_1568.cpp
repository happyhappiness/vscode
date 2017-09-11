void showLatencyDistSamples(struct distsamples *samples, long long tot) {
    int j;

    /* We convert samples into a number between 0 and DIST_GRAYS,
     * proportional to the percentage a given bucket represents.
     * This way intensity of the different parts of the spectrum
     * don't change relative to the number of requests, which avoids to
     * pollute the visualization with non-latency related info. */
    printf("\033[38;5;0m"); /* Set foreground color to black. */
    for (j = 0; ; j++) {
        float color = (float) samples[j].count / tot * LATENCY_DIST_GRAYS;
        color = ceil(color) + (LATENCY_DIST_MIN_GRAY-1);
        if (color == LATENCY_DIST_MIN_GRAY-1) {
            printf("\033[48;5;0m ");
        } else {
            printf("\033[48;5;%dm%c", (int)color, samples[j].character);
        }
        samples[j].count = 0;
        if (samples[j].max == 0) break; /* Last sample. */
    }
