static void win32_cleanup(void)
{
#ifdef USE_WINSOCK
  WSACleanup();
#endif
#ifdef USE_WINDOWS_SSPI
  Curl_sspi_global_cleanup();
#endif
}