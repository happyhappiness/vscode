 		if (set_reuse_addr(sockfd)) {
 			logerror("Could not set SO_REUSEADDR: %s", strerror(errno));
 			close(sockfd);
 			continue;
 		}
 
+		set_keep_alive(sockfd);
+
 		if (bind(sockfd, ai->ai_addr, ai->ai_addrlen) < 0) {
 			logerror("Could not bind to %s: %s",
 				 ip2str(ai->ai_family, ai->ai_addr, ai->ai_addrlen),
 				 strerror(errno));
 			close(sockfd);
 			continue;	/* not fatal */
