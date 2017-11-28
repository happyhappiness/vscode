mb.Printf("%i-Error: (%d) %s\r\n", scode,
                  request->errDetail,
                  strerror(request->errDetail));