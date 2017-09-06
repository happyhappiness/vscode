size = snprintf((char *)ntlmbuf, sizeof(ntlmbuf),
                    NTLMSSP_SIGNATURE "%c"
                    "\x03%c%c%c" /* type-3, 32 bits */

                    "%c%c" /* LanManager length */
                    "%c%c" /* LanManager allocated space */
                    "%c%c" /* LanManager offset */
                    "%c%c";