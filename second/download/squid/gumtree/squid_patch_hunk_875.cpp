     storeAppendPrintf(sentry, "no.not_entry_cachable\t%d\n",
                       store_check_cachable_hist.no.not_entry_cachable);
     storeAppendPrintf(sentry, "no.wrong_content_length\t%d\n",
                       store_check_cachable_hist.no.wrong_content_length);
     storeAppendPrintf(sentry, "no.negative_cached\t%d\n",
                       store_check_cachable_hist.no.negative_cached);
+    storeAppendPrintf(sentry, "no.missing_parts\t%d\n",
+                      store_check_cachable_hist.no.missing_parts);
     storeAppendPrintf(sentry, "no.too_big\t%d\n",
                       store_check_cachable_hist.no.too_big);
     storeAppendPrintf(sentry, "no.too_small\t%d\n",
                       store_check_cachable_hist.no.too_small);
     storeAppendPrintf(sentry, "no.private_key\t%d\n",
                       store_check_cachable_hist.no.private_key);
