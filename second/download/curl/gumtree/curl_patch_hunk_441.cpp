 "\n"
 "        curl -u username sftp://shell.example.com/etc/issue\n"
 "\n"
 "  Get a file from an SSH server using SCP using a private key to authenticate:\n"
 "\n"
 "        curl -u username: --key ~/.ssh/id_dsa --pubkey ~/.ssh/id_dsa.pub \\\n"
-"        	scp://shell.example.com/~/personal.txt\n"
+"            scp://shell.example.com/~/personal.txt\n"
 "\n"
 "  Get the main page from an IPv6 web server:\n"
 "\n"
 , stdout);
  fputs(
 "        curl -g \"http://[2001:1890:1112:1::20]/\"\n"
