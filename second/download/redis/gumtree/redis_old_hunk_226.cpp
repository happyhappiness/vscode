        }
        usleep(LATENCY_SAMPLE_RATE * 1000);
    }
}

/*------------------------------------------------------------------------------
 * Slave mode
 *--------------------------------------------------------------------------- */

/* Sends SYNC and reads the number of bytes in the payload. Used both by
 * slaveMode() and getRDB(). */
unsigned long long sendSync(int fd) {
