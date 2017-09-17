 * field is still a time_t stamp.  By doing that, it is possible for a site to
 * have a "flag second" in which they stop all of their old-format servers,
 * wait one entire second, and then start all of their new-servers.  This
 * procedure will ensure that the new space of identifiers is completely unique
 * from the old space.  (Since the first four unencoded bytes always differ.)
 */

static unsigned global_in_addr;

static APACHE_TLS unique_id_rec cur_unique_id;

static void unique_id_global_init(server_rec *s, pool *p)
{
#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 256
#endif
    char str[MAXHOSTNAMELEN + 1];
    struct hostent *hent;
#ifndef NO_GETTIMEOFDAY
    struct timeval tv;
#endif

    /*
     * First of all, verify some assumptions that have been made about the
     * contents of unique_id_rec.  We do it this way because it isn't
     * affected by trailing padding.
     */
    if (XtOffsetOf(unique_id_rec, counter) + sizeof(cur_unique_id.counter)
        != 14) {
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ALERT, s,
                    "mod_unique_id: sorry the size assumptions are wrong "
                    "in mod_unique_id.c, please remove it from your server "
                    "or fix the code!");
        exit(1);
    }

    /*
     * Now get the global in_addr.  Note that it is not sufficient to use one
     * of the addresses from the main_server, since those aren't as likely to
     * be unique as the physical address of the machine
     */
