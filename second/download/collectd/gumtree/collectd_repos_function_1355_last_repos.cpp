static int tape_read(void) {

#if HAVE_KSTAT_IO_T_WRITES && HAVE_KSTAT_IO_T_NWRITES && HAVE_KSTAT_IO_T_WTIME
#define KIO_ROCTETS reads
#define KIO_WOCTETS writes
#define KIO_ROPS nreads
#define KIO_WOPS nwrites
#define KIO_RTIME rtime
#define KIO_WTIME wtime
#elif HAVE_KSTAT_IO_T_NWRITTEN && HAVE_KSTAT_IO_T_WRITES &&                    \
    HAVE_KSTAT_IO_T_WTIME
#define KIO_ROCTETS nread
#define KIO_WOCTETS nwritten
#define KIO_ROPS reads
#define KIO_WOPS writes
#define KIO_RTIME rtime
#define KIO_WTIME wtime
#else
#error "kstat_io_t does not have the required members"
#endif
  static kstat_io_t kio;

  if (kc == NULL)
    return -1;

  if (numtape <= 0)
    return -1;

  for (int i = 0; i < numtape; i++) {
    if (kstat_read(kc, ksp[i], &kio) == -1)
      continue;

    if (strncmp(ksp[i]->ks_class, "tape", 4) == 0) {
      tape_submit(ksp[i]->ks_name, "tape_octets", kio.KIO_ROCTETS,
                  kio.KIO_WOCTETS);
      tape_submit(ksp[i]->ks_name, "tape_ops", kio.KIO_ROPS, kio.KIO_WOPS);
      /* FIXME: Convert this to microseconds if necessary */
      tape_submit(ksp[i]->ks_name, "tape_time", kio.KIO_RTIME, kio.KIO_WTIME);
    }
  }

  return 0;
}