     while (subkey)
     {
       shortid = subkey->keyid;
       len = mutt_strlen (subkey->keyid);
       if (len > 8)
         shortid += len - 8;
-      strftime (date, sizeof (date), "%Y-%m-%d", localtime (&subkey->timestamp));
+      tt = subkey->timestamp;
+      strftime (date, sizeof (date), "%Y-%m-%d", localtime (&tt));
 
       if (!more)
         fprintf (*fp, "%s %5.5s %d/%8s %s %s\n", more ? "sub" : "pub",
                  gpgme_pubkey_algo_name (subkey->pubkey_algo), subkey->length,
                  shortid, date, uid->uid);
       else
