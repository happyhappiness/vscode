fputs(
"              --proto for how protocols are represented.\n"
"\n"
"              Example, allow only HTTP and HTTPS on redirect:\n"
"\n"
"               curl --proto-redir -all,http,https http://example.com\n"
"\n"
"              By default curl will allow all protocols on redirect except sev-\n"
"              eral disabled for security reasons: Since 7.19.4  FILE  and  SCP\n"
"              are  disabled,  and since 7.40.0 SMB and SMBS are also disabled.\n"
, stdout);