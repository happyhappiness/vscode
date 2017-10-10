 void transport_take_over(struct transport *transport,
 			 struct child_process *child)
 {
 	struct git_transport_data *data;
 
 	if (!transport->smart_options)
-		die("Bug detected: Taking over transport requires non-NULL "
+		die("BUG: taking over transport requires non-NULL "
 		    "smart_options field.");
 
 	data = xcalloc(1, sizeof(*data));
 	data->options = *transport->smart_options;
 	data->conn = child;
 	data->fd[0] = data->conn->out;
