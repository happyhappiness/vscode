 		 * xd[0], spits out band#2 to stderr, and feeds us band#1
 		 * through demux->out.
 		 */
 		demux.proc = sideband_demux;
 		demux.data = xd;
 		demux.out = -1;
+		demux.isolate_sigpipe = 1;
 		if (start_async(&demux))
 			die("fetch-pack: unable to fork off sideband"
 			    " demultiplexer");
 	}
 	else
 		demux.out = xd[0];
