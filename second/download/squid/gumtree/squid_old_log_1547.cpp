mb.Printf("%i %s\r\n", header.getInt(HDR_FTP_STATUS),
                  (reason ? reason : 0));