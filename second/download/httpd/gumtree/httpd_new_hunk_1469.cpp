 * field is still a time_t stamp.  By doing that, it is possible for a site to
 * have a "flag second" in which they stop all of their old-format servers,
 * wait one entire second, and then start all of their new-servers.  This
 * procedure will ensure that the new space of identifiers is completely unique
 * from the old space.  (Since the first four unencoded bytes always differ.)
 */
/*
 * Sun Jun  7 05:43:49 CEST 1998 -- Alvaro
 * More comments:
 * 1) The UUencoding prodecure is now done in a general way, avoiding the problems
 * with sizes and paddings that can arise depending on the architecture. Now the
 * offsets and sizes of the elements of the unique_id_rec structure are calculated
 * in unique_id_global_init; and then used to duplicate the structure without the
 * paddings that might exist. The multithreaded server fix should be now very easy:
 * just add a new "tid" field to the unique_id_rec structure, and increase by one
 * UNIQUE_ID_REC_MAX.
 * 2) unique_id_rec.stamp has been changed from "time_t" to "unsigned int", because
 * its size is 64bits on some platforms (linux/alpha), and this caused problems with
 * htonl/ntohl. Well, this shouldn't be a problem till year 2106.
 */

static unsigned global_in_addr;

static APACHE_TLS unique_id_rec cur_unique_id;

/*
 * Number of elements in the structure unique_id_rec.
 */
#define UNIQUE_ID_REC_MAX 4

static unsigned short unique_id_rec_offset[UNIQUE_ID_REC_MAX],
                      unique_id_rec_size[UNIQUE_ID_REC_MAX],
                      unique_id_rec_total_size,
                      unique_id_rec_size_uu;

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
     * Calculate the sizes and offsets in cur_unique_id.
     */
    unique_id_rec_offset[0] = XtOffsetOf(unique_id_rec, stamp);
    unique_id_rec_size[0] = sizeof(cur_unique_id.stamp);
    unique_id_rec_offset[1] = XtOffsetOf(unique_id_rec, in_addr);
    unique_id_rec_size[1] = sizeof(cur_unique_id.in_addr);
    unique_id_rec_offset[2] = XtOffsetOf(unique_id_rec, pid);
    unique_id_rec_size[2] = sizeof(cur_unique_id.pid);
    unique_id_rec_offset[3] = XtOffsetOf(unique_id_rec, counter);
    unique_id_rec_size[3] = sizeof(cur_unique_id.counter);
    unique_id_rec_total_size = unique_id_rec_size[0] + unique_id_rec_size[1] +
                               unique_id_rec_size[2] + unique_id_rec_size[3];

    /*
     * Calculate the size of the structure when uuencoded.
     */
    unique_id_rec_size_uu = (unique_id_rec_total_size*8+5)/6;

    /*
     * Now get the global in_addr.  Note that it is not sufficient to use one
     * of the addresses from the main_server, since those aren't as likely to
     * be unique as the physical address of the machine
     */
