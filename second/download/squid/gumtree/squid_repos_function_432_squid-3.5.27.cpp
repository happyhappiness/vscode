const char *
obtain_challenge()
{
    int j = 0;
    const char *ch = NULL;
    for (j = 0; j < numcontrollers; ++j) {
        debug("obtain_challenge: selecting %s\\%s (attempt #%d)\n",
              current_dc->domain, current_dc->controller, j + 1);
        if (current_dc->dead != 0) {
            if (time(NULL) - current_dc->dead >= DEAD_DC_RETRY_INTERVAL) {
                /* mark helper as retry-worthy if it's so. */
                debug("Reviving DC\n");
                current_dc->dead = 0;
            } else {        /* skip it */
                debug("Skipping it\n");
                continue;
            }
        }
        /* else branch. Here we KNOW that the DC is fine */
        debug("attempting challenge retrieval\n");
        ch = make_challenge(current_dc->domain, current_dc->controller);
        debug("make_challenge retuned %p\n", ch);
        if (ch) {
            debug("Got it\n");
            return ch;      /* All went OK, returning */
        }
        /* Huston, we've got a problem. Take this DC out of the loop */
        debug("Marking DC as DEAD\n");
        current_dc->dead = time(NULL);
        /* Try with the next */
        debug("moving on to next controller\n");
        current_dc = current_dc->next;
    }
    /* all DCs failed. */
    return NULL;
}