 * the DNS caching.

 */

static char *

create_hostcache_id(char *server, int port)

{

  /* create and return the new allocated entry */

  return aprintf("%s:%d", server, port);

