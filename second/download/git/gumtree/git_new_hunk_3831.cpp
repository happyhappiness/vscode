	vsnprintf(msgbuf, PBUFFERSIZE, fmt, args);
	va_end(args);
	fprintf(stderr, "Transfer loop debugging: %s\n", msgbuf);
}

/* Stream state: More data may be coming in this direction. */
#define SSTATE_TRANSFERRING 0
/*
 * Stream state: No more data coming in this direction, flushing rest of
 * data.
 */
#define SSTATE_FLUSHING 1
/* Stream state: Transfer in this direction finished. */
#define SSTATE_FINISHED 2

#define STATE_NEEDS_READING(state) ((state) <= SSTATE_TRANSFERRING)
#define STATE_NEEDS_WRITING(state) ((state) <= SSTATE_FLUSHING)
#define STATE_NEEDS_CLOSING(state) ((state) == SSTATE_FLUSHING)

/* Unidirectional transfer. */
struct unidirectional_transfer {
	/* Source */
