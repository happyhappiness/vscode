 * \brief get string message of the last error
 *
 *  all function in this file will return 0 when success
 *  and -1 when an error occured,
 *  XGBGetLastError can be called to retrieve the error
 *
 *  this function is threadsafe and can be called by different thread
 * \return const char* error inforomation
 */
XGB_DLL const char *XGBGetLastError();

