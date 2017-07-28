package gumtree;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import com.github.gumtreediff.actions.ActionGenerator;
import com.github.gumtreediff.actions.model.Action;
import com.github.gumtreediff.actions.model.Addition;
import com.github.gumtreediff.actions.model.Insert;
import com.github.gumtreediff.actions.model.Update;
import com.github.gumtreediff.client.Run;
import com.github.gumtreediff.gen.Generators;
import com.github.gumtreediff.matchers.Mapping;
import com.github.gumtreediff.matchers.MappingStore;
import com.github.gumtreediff.matchers.Matcher;
import com.github.gumtreediff.matchers.Matchers;
import com.github.gumtreediff.tree.ITree;
import com.github.gumtreediff.tree.TreeContext;

import java.io.LineNumberReader;

public class GumTreeApi {
	private String oldFile, newFile;
	private TreeContext oldTreeContext, newTreeContext;
	private ITree oldTree, newTree;
	private Matcher matcher;
	private ActionGenerator actionGenerator;
	private MappingStore mappings;
	private List<Action> actions;
	// application specific info for compare two file
	private int oldLoc;
	private ITree oldLogNode, newLogNode;
	private List<ITree> oldLogs;
	final int LOG_OVER_MODIFY = -1;
	final int LOG_NO_MODIFY = 0;
	final int LOG_MODIFY = 1;
	final String COMMENT_TYPE = "comment";
	// application specific info for analyze file
	private int loc;
	private ITree tree;
	private ITree logNode;
	private TreeContext treeContext;
	private String filename;

	public void setOldAndNewFile(String oldFile, String newFile) {
		Run.initGenerators();
		try {
			this.oldFile = oldFile;
			this.newFile = newFile;
			// initialize treeContext and iTree
			oldTreeContext = Generators.getInstance().getTree(this.oldFile);
			newTreeContext = Generators.getInstance().getTree(this.newFile);
			oldTree = oldTreeContext.getRoot();
			newTree = newTreeContext.getRoot();
			// initialize matcher
			matcher = Matchers.getInstance().getMatcher(oldTree, newTree);
			matcher.match();
			mappings = matcher.getMappings();
			// initialize action generator
			actionGenerator = new ActionGenerator(oldTree, newTree, matcher.getMappings());
			actionGenerator.generate();
			actions = actionGenerator.getActions();
			// initialize application specific info
			oldLogs = new ArrayList<ITree>();
		} catch (Exception e) {
			// e.printStackTrace();
			System.out.println(e.toString());
			System.out.printf("oldFile: %s, newFile: %s \n", oldFile, newFile);
		}
	}

	public void setOldAndNewFile() {
		String oldFile = "/usr/info/code/cpp/LogMonitor/LogMonitor/second/gumtree/c/old.cpp";
		String newFile = "/usr/info/code/cpp/LogMonitor/LogMonitor/second/gumtree/c/new.cpp";
		this.setOldAndNewFile(oldFile, newFile);
	}

	public static void main(String args[]) {
		// System.out.println("hello I am gumtree api");
		// String oldFile =
		// "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/CMake/CMake-old-new/Kitware_CMake_old_hunk_11.cpp";
		// String newFile =
		// "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/CMake/CMake-old-new/Kitware_CMake_new_hunk_11.cpp";
		// GumTreeApi g = new GumTreeApi();
		// g.setOldAndNewFile(oldFile, newFile);
		// g.setOldLoc(15);
		// System.out.println(g.getNewLog());
		String filename = "/usr/info/code/cpp/LogMonitor/LogMonitor/second/download/CMake/CMake-old-new/Kitware_CMake_old_hunk_265.cpp";
		GumTreeApi g = new GumTreeApi();
		g.setFile(filename);
		g.setLoc(12);
		System.out.println(g.getLog());
//		GumTreeApi g = new GumTreeApi();
//		g.setOldAndNewFile();
//		g.addLogNode(5);
//		g.setOldLoc(5);
//		System.out.println(g.getActionType());
	}

	public boolean setOldLoc(int oldLoc) {
		this.oldLoc = oldLoc;
		this.oldLogNode = getTopNodeOfLine(this.oldLoc, this.oldTree, this.oldFile);
		// commented line
		if (oldLogNode == null) {
			System.out.printf("line: %d in file: %s no node found\n", this.oldLoc, this.oldFile);
			return false;
		}
		else if(this.oldTreeContext.getTypeLabel(this.oldLogNode).equals(COMMENT_TYPE))
		{
			System.out.printf("line: %d in file: %s found to be comment\n", this.oldLoc, this.oldFile);
			return false;
		}
		
//		printNode(this.oldLogNode, this.oldTreeContext, this.oldFile);
		this.newLogNode = mappings.getDst(this.oldLogNode);
		return true;
	}

	public int getOldLoc() {
		return this.oldLoc;
	}

	public String getOldLog() {
		return getValue(this.oldLogNode, this.oldFile);
	}

	public String getNewLog() {
		if (this.newLogNode == null)
			return null;
		else
			return getValue(this.newLogNode, this.newFile);
	}

	public int getNewLoc() {
		if (this.newLogNode == null)
			return -1;
		else
			return getLineNumber(this.newLogNode, this.newFile, true) - 1;
	}

	public void addLogNode(int line) {
		this.oldLogs.add(this.getTopNodeOfLine(line, this.oldTree, this.oldFile));
	}

	// one line to action type NO, OVER, ..
	public int getActionType() {
		if (actions.size() == 0) {
			return LOG_NO_MODIFY;
		}
		Iterator<Action> actionIter = actions.iterator();
		Action action;
		String changeType;
		ITree tempNode;
		boolean isLogModify = true;
		while (actionIter.hasNext()) {
			action = actionIter.next();
			// do not deal with comment modification
			if(this.isActionOfComment(action))
			{
				continue;
			}
			changeType = action.getName();
			// judge if leaf edition is edition of logs
			tempNode = changeType.equals("INS") ? ((Insert)action).getParent() : action.getNode();
			if (tempNode.isLeaf()) {
//				printNode(tempNode, this.oldTreeContext, this.oldFile);
				isLogModify = false;
				// traverse all log nodes
				Iterator<ITree> logIter = this.oldLogs.iterator();
				while (logIter.hasNext()) {
					if (isChildrenOf(tempNode, logIter.next())) {
						isLogModify = true;
						break;
					}
				}
				if (isLogModify == false) {
					return LOG_OVER_MODIFY;
				}
			}
		}

		return LOG_MODIFY;
	}

	public void setFile(String filename) {
		Run.initGenerators();
		try {
			this.filename = filename;
			// initialize treeContext and iTree
			this.treeContext = Generators.getInstance().getTree(this.filename);
			this.tree = this.treeContext.getRoot();
		} catch (Exception e) {
			// e.printStackTrace();
			System.out.println(e.toString());
			System.out.printf("filename: %s\n", filename);

		}
	}

	public boolean setLoc(int line) {
		this.loc = line;
		this.logNode = getTopNodeOfLine(this.loc, this.tree, this.filename);
		// commented line
		if (this.logNode == null) {
			System.out.printf("line: %d in file: %s no node found\n", this.loc, this.filename);
			return false;
		}
		// else
		// {
		// printNode(this.logNode, this.treeContext, this.filename);
		// }
		return true;
	}

	public String getLog() {
		return getValue(this.logNode, this.filename);
	}

	public boolean isMatch() {
		Iterator<Action> actionIter = actions.iterator();
		Action action;
		while (actionIter.hasNext()) {
			action = actionIter.next();
			if (!isActionOfComment(action) && !action.getName().equals("UPD")) {
				return false;
			}
		}
		return true;
	}

	// judge whether an action is about comment
	private boolean isActionOfComment(Action action)
	{
		boolean isComment;
		ITree operatedNode = action.getNode();
		switch(action.getName())
		{
		case "INS":
			isComment = this.newTreeContext.getTypeLabel(operatedNode).equals(COMMENT_TYPE);
			break;
		default:
			isComment = this.oldTreeContext.getTypeLabel(operatedNode).equals(COMMENT_TYPE);
			break;
		}
		return isComment;
	}
	// one line to src node
	private ITree getTopNodeOfLine(int line, ITree rootNode, String filename) {
		// ITree topNode = isOld ? oldTree : newTree;
		line = line + 1;
		Iterator<ITree> allNodesIter = rootNode.getDescendants().iterator();
		ITree tempNode, largestNode = null;

		while (allNodesIter.hasNext()) {
			tempNode = allNodesIter.next();
			// printNode(tempNode, isOld);
			// the node with most children in given line
			if (getLineNumber(tempNode, filename, true) == line
					&& (largestNode == null || tempNode.getSize() > largestNode.getSize())) {
				largestNode = tempNode;
			}
		}

		// printNode(largestNode, isOld);
		return largestNode;
	}

	// is parentNode is one of the parents of node
	private boolean isChildrenOf(ITree node, ITree parentNode) {
		boolean isChildren = false;
		Iterator<ITree> parents = node.getParents().iterator();
		ITree tempNode;
		while (parents.hasNext()) {
			tempNode = parents.next();
			if (tempNode.equals(parentNode)) {
				isChildren = true;
				break;
			}
		}

		return isChildren;
	}

	// print node
	private void printNode(ITree node, TreeContext treeContext, String filename) {
		System.out.printf("node value: %s, type:%s, line: %d, size: %d \n", getValue(node, filename),
				treeContext.getTypeLabel(node.getType()), getLineNumber(node, filename, true), node.getSize());

	}

	// get text value of given node
	private String getValue(ITree node, String filename) {
		int beginPos = node.getPos();
		int endPos = node.getEndPos();
		// System.out.printf("beginPos: %d, endPos: %d\n", beginPos, endPos);

		// String filename = isOld ? oldFile : newFile;
		try {
			FileReader fileReader;
			fileReader = new FileReader(filename);
			fileReader.skip(beginPos);

			char[] value = new char[1000];
			fileReader.read(value, 0, endPos - beginPos);
			fileReader.close();

			return String.valueOf(value).trim();
		} catch (Exception e) {
			// e.printStackTrace();
			System.out.println(e.toString());
			System.out.printf("filename: %s, beginPos: %d, endPos:%d \n", filename, beginPos, endPos);
			return "";
		}
	}

	// get start line number of given node
	private int getLineNumber(ITree node, String filename, boolean isStart) {
		// String filename = isOld ? oldFile : newFile;
		int characterPos = isStart ? node.getPos() : node.getEndPos();
		LineNumberReader lineReader;
		int lineNumber = -1;
		try {
			lineReader = new LineNumberReader(new FileReader(filename));
			lineReader.skip(characterPos);

			lineNumber = lineReader.getLineNumber() + 1;
			lineReader.close();
		} catch (Exception e) {
			// e.printStackTrace();
			System.out.println(e.toString());
			System.out.printf("filename: %s, beginPos: %d \n", filename, characterPos);
			return -1;
		}

		return lineNumber;
	}

	/*
	 * public void getMapping(String oldFile, String newFile) {
	 * Run.initGenerators(); try {// parse to get tree info TreeContext
	 * oldTreeContext = Generators.getInstance().getTree(oldFile); TreeContext
	 * newTreeContext = Generators.getInstance().getTree(newFile); ITree oldTree =
	 * oldTreeContext.getRoot(); ITree newTree = newTreeContext.getRoot(); // match
	 * two trees Matcher m = Matchers.getInstance().getMatcher(oldTree, newTree);
	 * m.match(); Iterator<Mapping> mappingIter = m.getMappings().iterator(); ITree
	 * srcNode, dstNode; while(mappingIter.hasNext()) { Mapping mapping =
	 * mappingIter.next(); srcNode = mapping.getFirst(); dstNode =
	 * mapping.getSecond();
	 * System.out.printf("1) src info. type:%s, value:%s, line:%d \n",
	 * oldTreeContext.getTypeLabel(srcNode), getValue(srcNode, oldFile),
	 * getLineNumber(srcNode, oldFile, true));
	 * System.out.printf("2) dst info. type:%s, value:%s, line:%d \n",
	 * newTreeContext.getTypeLabel(dstNode), getValue(dstNode, newFile)
	 * dstNode.getLabel(), getLineNumber(dstNode, newFile, true)); } // generate
	 * actions ActionGenerator actionGenerator = new ActionGenerator(oldTree,
	 * newTree, m.getMappings()); actionGenerator.generate(); List<Action> actions =
	 * actionGenerator.getActions();
	 * System.out.printf("3) element edit distance: %d \n", actions.size()); }
	 * catch(UnsupportedOperationException | IOException e) { e.printStackTrace(); }
	 * }
	 * 
	 * 
	 * public void getAction(String oldFile, String newFile) { Run.initGenerators();
	 * try { // parse to get tree info TreeContext oldTreeContext =
	 * Generators.getInstance().getTree(oldFile); TreeContext newTreeContext =
	 * Generators.getInstance().getTree(newFile); ITree oldTree =
	 * oldTreeContext.getRoot(); ITree newTree = newTreeContext.getRoot(); // match
	 * two trees Matcher m = Matchers.getInstance().getMatcher(oldTree, newTree);
	 * m.match(); m.getMappings(); // generate actions ActionGenerator
	 * actionGenerator = new ActionGenerator(oldTree, newTree, m.getMappings());
	 * actionGenerator.generate(); List<Action> actions =
	 * actionGenerator.getActions(); // parse actions according to type Action
	 * action; ITree tempNode; for(Iterator<Action> iter = actions.iterator();
	 * iter.hasNext(); ) { action = iter.next(); // change type String changeType =
	 * action.getName(); System.out.printf("1) change info. change type: %s \n",
	 * changeType); // value and loc info String oldValue = ""; String newValue =
	 * ""; int oldLoc = -1; int newLoc = -1; switch(changeType) { // INSERT: new
	 * value, new loc case "INS": tempNode = action.getNode(); newValue =
	 * tempNode.getLabel(); newLoc = getLineNumber(tempNode, newFile, true); break;
	 * // UPDATE: old / new value; old loc[old value and old loc by default] case
	 * "UPD": newValue = ((Update)action).getValue(); // MOVE/DELETE: old value, old
	 * loc default: tempNode = action.getNode(); oldValue = tempNode.getLabel();
	 * oldLoc = getLineNumber(tempNode, oldFile, true); break; }
	 * System.out.printf("2) old info. value: %s, line: %d \n", oldValue, oldLoc);
	 * System.out.printf("3) new info. value:%s, line:%d \n", newValue, newLoc); } }
	 * catch (UnsupportedOperationException | IOException e) { e.printStackTrace();
	 * } } // get start line number of given node int getLineNumber(ITree node,
	 * String filename, boolean isStart) { int characterPos = isStart ?
	 * node.getPos() : node.getEndPos(); LineNumberReader lineReader; int lineNumber
	 * = -1; try { lineReader = new LineNumberReader(new FileReader(filename));
	 * lineReader.skip(characterPos);
	 * 
	 * lineNumber = lineReader.getLineNumber() + 1; //
	 * System.out.println(lineReader.readLine()); lineReader.close(); } catch
	 * (IOException e) { e.printStackTrace(); }
	 * 
	 * return lineNumber; }
	 * 
	 * // get text value of given tree node String getValue(ITree node, String
	 * filename) { int beginPos = node.getPos(); int endPos = node.getEndPos(); try
	 * { FileReader fileReader; fileReader = new FileReader(filename);
	 * fileReader.skip(beginPos);
	 * 
	 * char[] value = new char[100]; fileReader.read(value, 0, endPos - beginPos);
	 * fileReader.close();
	 * 
	 * return String.valueOf(value).trim(); } catch (IOException e) {
	 * e.printStackTrace(); return ""; } }
	 */
	
//	if(action.getName().equals("INS"))
//	{
//		printNode(action.getNode(), this.newTreeContext, this.newFile);
//		printNode(((Insert)action).getParent(), this.oldTreeContext, this.oldFile);
//	}
//	else
//	{
//		printNode(action.getNode(), this.oldTreeContext, this.oldFile);
//	}

}
