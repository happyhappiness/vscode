*userp = aprintf( "%sAuthorization: Basic %s\015\012",
                      proxy?"Proxy-":"",
                      authorization);