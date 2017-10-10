 					break;
 					}
 				}
 			} while (ack);
 			flushes--;
 			if (got_continue && MAX_IN_VAIN < in_vain) {
-				if (args->verbose)
-					fprintf(stderr, "giving up\n");
+				print_verbose(args, _("giving up"));
 				break; /* give up */
 			}
 		}
 	}
 done:
 	if (!got_ready || !no_done) {
 		packet_buf_write(&req_buf, "done\n");
 		send_request(args, fd[1], &req_buf);
 	}
-	if (args->verbose)
-		fprintf(stderr, "done\n");
+	print_verbose(args, _("done"));
 	if (retval != 0) {
 		multi_ack = 0;
 		flushes++;
 	}
 	strbuf_release(&req_buf);
 
 	if (!got_ready || !no_done)
 		consume_shallow_list(args, fd[0]);
 	while (flushes || multi_ack) {
 		int ack = get_ack(fd[0], result_sha1);
 		if (ack) {
-			if (args->verbose)
-				fprintf(stderr, "got ack (%d) %s\n", ack,
-					sha1_to_hex(result_sha1));
+			print_verbose(args, _("got %s (%d) %s"), "ack",
+				      ack, sha1_to_hex(result_sha1));
 			if (ack == ACK)
 				return 0;
 			multi_ack = 1;
 			continue;
 		}
 		flushes--;
