    if (ls->samples) ls->mad = sum / ls->samples;
}

/* ---------------------- Latency command implementation -------------------- */

/* latencyCommand() helper to produce a time-delay reply for all the samples
