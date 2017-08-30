 * the DNS caching.

 */

static char *

create_hostcache_id(const char *server, int port)

{

  /* create and return the new allocated entry */

  return aprintf("%s:%d", server, port);

