printf("%llu %ss with %llu %s (%05.2f%% of keys, avg size %.2f)\n",
           counts[i], typename[i], totalsize[i], typeunit[i],
           sampled ? 100 * (double)counts[i]/sampled : 0,
           counts[i] ? (double)totalsize[i]/counts[i] : 0);