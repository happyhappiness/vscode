mb.appendf("%i %s\r\n", header.getInt(Http::HdrType::FTP_STATUS),
                   (reason ? reason : 0));