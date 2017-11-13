fputs(
"              Tells  curl to limit what protocols it may use on redirect. Pro-\n"
"              tocols denied by --proto are not overridden by this option.  See\n"
"              --proto for how protocols are represented.\n"
"\n"
"              Example, allow only HTTP and HTTPS on redirect:\n"
"\n"
"               curl --proto-redir -all,http,https http://example.com\n"
"\n"
"              By default curl will allow all protocols on redirect except sev-\n"
, stdout);