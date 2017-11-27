 
 /* public function */
 void handle_pcap(u_char *udata, const struct pcap_pkthdr *hdr, const u_char *pkt)
 {
     int status;
 
-    DEBUG ("handle_pcap (udata = %p, hdr = %p, pkt = %p): hdr->caplen = %i\n",
+    fprintf (stderr, "handle_pcap (udata = %p, hdr = %p, pkt = %p): hdr->caplen = %i\n",
 		    (void *) udata, (void *) hdr, (void *) pkt,
 		    hdr->caplen);
 
     if (hdr->caplen < ETHER_HDR_LEN)
 	return;
 
