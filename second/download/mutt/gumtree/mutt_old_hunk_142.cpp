    fputs ("X-Mutt-SMIME: ", msg->fp);
    if (hdr->security & ENCRYPT) {
	fputc ('E', msg->fp);
	if (SmimeCryptAlg && *SmimeCryptAlg)
	    fprintf (msg->fp, "C<%s>", SmimeCryptAlg);
    }
    if (hdr->security & SIGN) {
	fputc ('S', msg->fp);
	if (SmimeDefaultKey && *SmimeDefaultKey)
	    fprintf (msg->fp, "<%s>", SmimeDefaultKey);
    }
    if (hdr->security & INLINE)
