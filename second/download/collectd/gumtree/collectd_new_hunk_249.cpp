 *  This function is called by reading processes with the values they've
 *  aquired. The function fetches the data-set definition (that has been
 *  registered using `plugin_register_data_set') and calls _all_ registered
 *  write-functions.
 *
 * ARGUMENTS
 *  `vl'        Value list of the values that have been read by a `read'
 *              function.
 */
int plugin_dispatch_values (value_list_t *vl);

int plugin_dispatch_notification (const notification_t *notif);

void plugin_log (int level, const char *format, ...)
	__attribute__ ((format(printf,2,3)));

