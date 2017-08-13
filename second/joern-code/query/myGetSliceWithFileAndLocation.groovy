/**
   write by Sarah
*/


/**
   Retrieve nodes from index using a Lucene query.
   
   @param query The lucene query to run
   
*/
Object.metaClass.getFileByName = { filename, honorVisibility = true ->
  	query = "$NODE_TYPE:$TYPE_FILE AND $NODE_FILEPATH:$filename"
	queryNodeIndex(query, honorVisibility)
}

Object.metaClass.getNodeByIndex = { id, honorVisibility = true ->
  	query = "id:$id"
	queryNodeIndex(query, honorVisibility)
}

Object.metaClass.hasCFG = { filename, honorVisibility = true ->
  	query = "$NODE_TYPE:$TYPE_FILE AND $NODE_FILEPATH:$filename"
	queryNodeIndex(query, honorVisibility).out('IS_FILE_OF').out('IS_FUNCTION_OF_CFG')
}

Object.metaClass.getStatementByFileNameAndLoc = { filename, loc, honorVisibility = true ->
	query = "$NODE_TYPE:$TYPE_FILE AND $NODE_FILEPATH:$filename"
	queryNodeIndex(query, honorVisibility).out('IS_FILE_OF').filter{it != null}
	.functionToStatements().filter{ it.location != null && it.location.startsWith(loc)}
}


// Object.metaClass.sliceForLogStatement = { it, order, edgeTypes, honorVisibility = true ->
//   	backward = it.sliceBackFromArgument()
//   	forward_arg = it.sliceForwardFromArgument()
//   	forward_ass = it.sliceForwardFromAssign()
//   	it.transform{backward; forward_arg; forward_ass}
// }


  /////////////////////////////////////////////////
 //     Corresponding Gremlin Steps             //
/////////////////////////////////////////////////

/**
  	getLogStatementBy Filename and location in file
*/

Gremlin.defineStep('getFileByName', [Vertex,Pipe], { filename, c = [] ->
 _()._emitForFunctions({ getFileByName( filename) }, c )
});

Gremlin.defineStep('getNodeByIndex', [Vertex,Pipe], { id, c = [] ->
 _()._emitForFunctions({ getNodeByIndex( id) }, c )
});

Gremlin.defineStep('getNodeById', [Vertex,Pipe], { id, c = [] ->
 _()._emitForFunctions({ getNodeByIndex( id) }, c )
});

Gremlin.defineStep('getNodeById', [Vertex,Pipe],{ id ->
	_().id.idsToNodes()
});

Gremlin.defineStep('hasCFG', [Vertex,Pipe], { filename, c = [] ->
 _()._emitForFunctions({ hasCFG( filename) }, c )
});

Gremlin.defineStep('getStatementByFileNameAndLoc', [Vertex,Pipe], { filename, loc, c = [] ->
 _()._emitForFunctions({ getStatementByFileNameAndLoc( filename, loc) }, c )
});


/**
  	with g and basic steps 
*/

// input: filename and location
// output: log node
Gremlin.defineStep('getLogByFileAndLoc', [Vertex,Pipe], { file, loc ->
 	_().transform{
		g.V("type","File").filter{ it.filepath.contains(file) } 
		.out("IS_FILE_OF").functionToStatements().has("location").filter{ it.location.startsWith(loc) }.as("log")
		.select(["log"]){ [it.id, it.code, it.type, it.location] }
	 }.scatter()
});

// input: start v and end v
// output: flow to edge (control) of in node id 
Gremlin.defineStep('getControlLabel', [Vertex,Pipe], { startV, endV ->
 	_().transform{
		g.V[startV].as("start")
		.inE("FLOWS_TO").as("label") // from destation to get flow label (just condition)
		.outV()
		.loop("start"){ it.object.id != endV }{ it.object.id == endV }
		.select(["label"]){ it.flowLabel }.toSet()
	}.scatter()
});
 

// input: log id and loop order
// output: id, code and type of control node
Gremlin.defineStep('getControlDependence', [Vertex,Pipe], { log, order -> // int, int 
 	_().transform{
		g.V[log].as("start") // get log
		.in("CONTROLS").as("control")
		.loop("start"){ it.loops < order }{ it.object.type == "Condition" }
		.select(["control"]){ [it.id, it.code, it.type, it.location] } // select type, id, code, type
	}
});

/*
----------"IdentifierDeclStatement", "Parameter", "ExpressionStatement"
=--- "IdentifierDeclType"
=--- "ParameterType" 
----------children() + "childNum"
=--- "PrimaryExpression", "CallExpression", "Identifier"
=--- "Callee"
*/

// input: log id
// output: id, code and type of control node
Gremlin.defineStep('getDefDependence', [Vertex,Pipe], { startV -> // int, int 
 	_().transform{
		g.V[startV]
		.inE("REACHES").as("var")
		.outV.as("def")
		.select(["var","def"])
		{ it.var }{ [it.id, it.code, it.type, it.location] } // select type, id, code, type
	}
});

// input node id [parameter or identifier decl]
// output var type
Gremlin.defineStep('getVarTypeForParaOrDecl', [Vertex,Pipe], { node_id ->
	_().transform{
		g.V[node_id].ifThenElse{ it.type == "Parameter" }
		{ it.out().has("type","ParameterType") } // for parameter
		{ it.has("type","IdentifierDeclStatement").astNodes().has("type","IdentifierDeclType") }// for decl statement
		.code
	}.scatter()
});

// input node id [expression statement]
// output right value type
Gremlin.defineStep('getRightValueType', [Vertex,Pipe], { node_id ->
	_().transform{
		g.V[node_id] // expression statement
		.children() // asssignment Expr
		.children().has("childNum", "1")
		.type
	}.scatter()
});

// input node id [expression statement]
// output Callee
Gremlin.defineStep('getCallee', [Vertex,Pipe], { node_id ->
	_().transform{
		g.V[node_id] // expression statement
		.astNodes()
		.has("type", "Callee")
		.code
	}.scatter()
});

// input node id AndExpression, OrExpression, UnaryOp, // RelationalExpression 
// output sub expression
Gremlin.defineStep('getSubExpressions', [Vertex,Pipe], { node_id ->
	_().transform{
		BOOL_OPERATOR_LIST = ['AndExpression', 'OrExpression', 'UnaryOp', 'RelationalExpression']
		g.V[node_id] // condition statement
		.children()
		.loop(1){ it.object.has("type", T.in, BOOL_OPERATOR_LIST).count() != 0 }
		{ it.object.type != 'UnaryOp' }
		.order{ it.b.id <=> it.a.id }.as("result")
		.select(["result"]){ [it.id, it.code, it.type, it.operator]}
	}.scatter()
});


// input node id 
// output Argument
Gremlin.defineStep('getArguments', [Vertex,Pipe], { node_id ->
	_().transform{
		g.V[node_id] // expression statement
		.astNodes()
		.has("type", "Argument")
		.children().as("result")
		.select(["result"]){ [it.id, it.code, it.type]}
	}.scatter()
});

// input node id [expression statement]
// output right children with primary Expression
Gremlin.defineStep('getIdentifier', [Vertex,Pipe], { node_id ->
	_().transform{
		g.V[node_id] // expression statement
		.children()
		.loop(1){ it.object.type != "CallExpression" }
		{ it.object.type == 'Identifier' }
		.code
	}.scatter()
});

// input node id [expression statement]
// output right children with primary Expression
Gremlin.defineStep('getPrimaryExpression', [Vertex,Pipe], { node_id ->
	_().transform{
		g.V[node_id] // expression statement
		.children()
		.loop(1){ it.object.type != "CallExpression" }
		{ it.object.type == "PrimaryExpression" }
		.code
	}.scatter()
});

// input: 
// output: flow to edge (control) of in node id 
Gremlin.defineStep('getFlowlabel', [Vertex,Pipe], {
 	_().inE("FLOWS_TO").ifThenElse{ it.flowLabel != ""} // first statement upon
	 { it } // return first statement
	 { it.as("start").outV().inE("FLOWS_TO").loop("start")
		{ it.object.flowLabel == "" } // loop utile find flowlable
		{ it.object.flowLabel != "" } // emit node with right out id	
	 }	
});

// input: log id and loop order
// output: type of flow, id, code and type of control node
Gremlin.defineStep('getCFGControlByLog', [Vertex,Pipe], { log, order -> // int, int 
 	_().transform{
		g.V[log].as("start") // get log
		.getFlowlabel().as("type")	 // from destation to get flow label (just condition)
		.back("start").in("CONTROLS")
		.has("type", "Condition").as("node")// get control edge
		.loop("start"){ it.loops < order }{ true } // loop to get type and node [FLOWS_TO]
		.select(["type","node"]){ it.flowLabel }{ [it.id, it.isCFGNode, it.code, it.type] } // select type, id, code, type
	}
});

// input: 
// output: postfix expression list 
Gremlin.defineStep('getCFGStatementLists', [Vertex,Pipe], { neighbor ->
	_().transform{
		baseTypeList = ["Identifier", "PrimaryExpression", "UnaryOperator"]
		exceptTypeList = ["CallExpression"]
		g.V[neighbor].ifThenElse{ it.type == "CFGEntryNode"} // it.children().toSet().size() == 0
		{ it.code } // no children
		{ it.as("start") // loop start
			.children().loop("start"){true}{true} // traverse the tree
			.order{ it.b.id <=> it.a.id } // post fix with order by id
			.ifThenElse{ it.has("type", T.in, baseTypeList).count() != 0 }  // retrieve code 
			{ it.code } // function call or leaf -> get code 
			{ it.has("operator").operator } // retrieve operator
		}
	 }
});


// input: statement id
// output: variable type
Gremlin.defineStep('getVarMap', [Vertex,Pipe], { statement -> // int
 	_().transform{
	 	g.V[statement].out("USE").as("use").in("DEF") // get DEF node
	    .getVarType().as("def")
		.select{ it.code }{ it.code } // vairable name and type
	}
});

// input: statement id
// output: variable type for ddg since it is def statement
Gremlin.defineStep('getVarType', [Vertex,Pipe], { 
	_().ifThenElse{ it.type == "Parameter" }{ it.out().has("type","ParameterType") } // for parameter
	{ it.has("type","IdentifierDeclStatement").astNodes().has("type","IdentifierDeclType") }// for decl statement
});

// input: statement id
// output: variable type for ddg since it is def statement
Gremlin.defineStep('getVarMapForDDG', [Vertex,Pipe], { statement -> // int
 	_().transform{
	 	g.V[statement]
		.as("start").out("DEF").as("use")
		.back("start").ifThenElse{ it.type == "Parameter" || it.type == "IdentifierDeclStatement" } 
		{ it.getVarType() } // get var type from itself
		{ it.out("DEF").in("DEF") // get DEF node of it defs
			.getVarType()
		}.as("def")
		.select(["use", "def"]){ it.code }{ it.code } // vairable name and type
	}
});

// // input: statement id
// // output: variable type (return type of functions)
// Gremlin.defineStep('getVarMapReturn', [Vertex,Pipe], { statement -> // int, string
//  	_().transform{
// 	 	g.V[statement].out("USE").as("use").in("DEF") // get DEF node
// 	    .ifThenElse{ it.type == "Parameter" }{ it.out().has("type","ParameterType") } // for parameter
// 		{ it.ifThenElse{ it.type == "IdentifierDeclStatement" }{ it.astNodes().has("type","IdentifierDeclType") } // for decl statement
// 			{ it.has("type","AssignmentExpr").astNodes().has("type","callee").getFunctionInfo() } // for assignEpression
// 		}
// 		.as("def").select{ it.code }{ it.code } // variable name and type
// 	}
// });

// // input: 
// // output: postfix expression list 
// Gremlin.defineStep('getConditionPast', [Vertex,Pipe], {
// 	_().transform{
// 		x = [];
// 		baseTypeList = ["CallExpression", "Identifier", "PrimaryExpression", "UnaryOperator"]
// 		// operatorTypeList = ["CallExpression", "Identifier", "PrimaryExpression", "UnaryOperator"]
// 		exceptTypeList = ["CallExpression"]
// 		it.as("start") // loop start
// 		.has("type", T.notin, exceptTypeList).children().loop("start"){true}{true} // traverse the tree
// 		.order{ it.b.id <=> it.a.id } // post fix with order by id
// 		.ifThenElse{ it.has("type", T.in, baseTypeList).count() != 0 }  // retrieve code 
// 		{ it.ifThenElse{ it.type == "CallExpression" }{ it.callToCallee().code }{ it.code } } // function call or leaf -> get code 
// 		{ it.operator }.fill(x); // retrieve operator
// 		x + it.operator
// 	 }
// });


// input: 
// output: postfix expression list 
Gremlin.defineStep('getCondition', [Vertex,Pipe], {
	_().transform{
		x = [];
		baseTypeList = ["Identifier", "PrimaryExpression", "UnaryOperator"]
		// operatorTypeList = ["CallExpression", "Identifier", "PrimaryExpression", "UnaryOperator"]
		exceptTypeList = ["CallExpression"]
		it.as("start") // loop start
		.children().loop("start"){true}{true} // traverse the tree
		.order{ it.b.id <=> it.a.id } // post fix with order by id
		.ifThenElse{ it.has("type", T.in, baseTypeList).count() != 0 }  // retrieve code 
		{ it.code } // function call or leaf -> get code 
		{ it.has("operator").operator }.fill(x); // retrieve operator
		x + it.ifThenElse{ it.has("type", T.in, baseTypeList).count() != 0 }{ it.code }{ it.has("operator").operator }
	 }
});


// input: condition id
// output: condition lists with additional list
Gremlin.defineStep('getConditionListByid', [Vertex,Pipe], { condition -> // int
 	_().transform{
		g.V[condition].as("start") // loop start
		.children().loop("start")
		{ it.object.type == "AndExpression" } // split and expression
		{ it.object.type != "AndExpression"} // deal sub expression
		.getCondition()
	}
});

// input: condition id
// output: condition lists with additional list
// get condition for switch case 
// no use
Gremlin.defineStep('getConditionListByidSwitch', [Vertex,Pipe], { condition -> // int, lists
 	_().transform{
		x = [];
		g.V[condition]
		.ifThenElse{ it.type == "CallExpression" }  
		{ it.callToCallee().code } // function name for call expression
		{ it.code }.fill(x); // code for others
		x
	}	
});


// input: 
// output: all functions
Gremlin.defineStep('getFunctions', [Vertex,Pipe], {
 	_().transform{
		g.V("type","Function").name.toSet()
	 }
});

// input: 
// output: all callees
Gremlin.defineStep('getFunctionCallees', [Vertex,Pipe], {
 	_().transform{
		g.V("type","Callee").code.toSet()
	 }
});


// input: 
// output: function return type node
Gremlin.defineStep('getFunctionInfo', [Vertex,Pipe], {
	_().transform{
		functionName = it.code;
 		getFunctionsByName(functionName).out("IS_FUNCTION_OF_AST").out().has("type","ReturnType")
	 }
});

// input: log statement
// output: [statement, variable] ... (one variable can have at most order record)
Gremlin.defineStep('getDDG', [Vertex,Pipe], { log ->
 	_().transform{
		g.V[log].inE("REACHES").as("edge") // get each edge
		.var.as("variable") // get variable
		.back("edge").outV().as("ddg") // get ddg node
		.select( ["variable", "ddg"] ){ it }{ [it.id, it.isCFGNode, it.code, it.type] } // select id, isCFGNode, code, type and variable name
	 }
});


// input: log statement
// output: [static string] ... (static string list)
Gremlin.defineStep('getStaticStr', [Vertex,Pipe], { log ->
 	_().transform{
		g.V[log]
		.astNodes() // select id, isCFGNode, code, type and variable name
		.has("type", "PrimaryExpression").code
	}
});

// input: functionId
// output: file name
Gremlin.defineStep('getFileInfo', [Vertex,Pipe], { function_id ->
	// _().as("start").in("CONTROLS").loop("start") 
	// { it.object.type != "CFGEntryNode" }{ it.object.type == "CFGEntryNode" } // get entry node
	// .in("IS_FUNCTION_OF_CFG").in("IS_FILE_OF") // get file

	_().transform{
		g.V[function_id].in("IS_FILE_OF").filepath
	}
})

// input: log function name
// output: call statement, call file, call location 
Gremlin.defineStep('logToCallStatements', [Vertex,Pipe], { log_function ->
	_().transform{
		g.V("type","Callee") // get all callee
		.filter{ it.code == log_function } // callee with name specified by log_function	
		.as("start").parents().loop("start"){ it.object.isCFGNode != "True" }{ it.object.isCFGNode == "True" } // loop util find contained statement
		// getCallsTo(log_function)
		// .parents()
		.as("statement")
		.select(["statement"]){ [ it.id, it.code, it.location, it.functionId ] }//{ it.filepath } // output id, code, location and file name
		
	}.scatter()
})

// input: log id(int)
// output: log block info
Gremlin.defineStep('logToLogBlock', [Vertex,Pipe], { log_id ->
 	_().transform{
		g.V[log_id]// get log
		.in("CONTROLS").as("node")
		.select(["node"]){ [it.id, it.location, it.functionId, it.type] }.scatter() // select type, id, code, type
	}.scatter()
})

// input: log id(int)
// output: flag
Gremlin.defineStep('logToLogBlockFlag', [Vertex,Pipe], { log_id ->
 	_().transform{
		g.V[log_id]// get log
		.getFlowlabel().flowLabel
	}.scatter()
})

// input: nothing
// output: all ast node type
Gremlin.defineStep('getAllASTNodeType', [Vertex,Pipe], {
 	_().transform{
		g.V.hasNot("isCFGNode")// get AST Node
		.type.toSet()
	}.scatter()
})

Gremlin.defineStep('myASTNodes', [Vertex, Pipe], {
	_().children().loop(1){true}{true}
})


// input: block id 
// output: block condition type
Gremlin.defineStep('getBlockCondition', [Vertex,Pipe], { blockId ->
 	_().transform{
		g.V[blockId] // condition
		.myASTNodes().order{ it.b.id <=> it.a.id }.type // post order of ast node
	}.scatter()
})

// input: block id and flag
// output: block statements type
Gremlin.defineStep('getBlockStatements', [Vertex,Pipe], { blockId, flag ->
 	_().transform{
		g.V[blockId] // condition
		.out("CONTROLS").as("statement").getFlowlabel() // statement under flag
		.filter{ it.flowLabel == flag }
		.back("statement") // back to statement
		.ifThenElse{ it.type == "Condition"} // first statement upon
		{ it.type } // do not deal with condition statement
		{ it.myASTNodes().order{ it.b.id <=> it.a.id }.type } // post order of ast node
	}.scatter()
})

// Gremlin.defineStep('slicerForLogStatement', [Vertex, Pipe], { order = 5, edgeTypes = ['REACHES', 'CONTROLS'] ->
//  // _()._emitForFunctions({ sliceForLogStatement( order, edgeTypes) }, c )
//  _().sliceBackFromArgument(order, edgeTypes).astNodes()
// })