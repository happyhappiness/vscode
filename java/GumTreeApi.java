package gumtree;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import com.github.gumtreediff.actions.ActionGenerator;
import com.github.gumtreediff.actions.model.Action;
import com.github.gumtreediff.actions.model.Addition;
import com.github.gumtreediff.actions.model.Update;
import com.github.gumtreediff.client.Run;
import com.github.gumtreediff.gen.Generators;
import com.github.gumtreediff.matchers.Mapping;
import com.github.gumtreediff.matchers.Matcher;
import com.github.gumtreediff.matchers.Matchers;
import com.github.gumtreediff.tree.ITree;
import com.github.gumtreediff.tree.TreeContext;

import java.io.LineNumberReader;

public class GumTreeApi {
	
	public static void main(String args[])
	{
		System.out.println("hello I am gumtree api");
		String old_file = "/usr/info/code/cpp/LogMonitor/LogMonitor/second/gumtree/c/old.cpp";
	    String new_file = "/usr/info/code/cpp/LogMonitor/LogMonitor/second/gumtree/c/new.cpp";
		/*String old_file = "/usr/info/code/cpp/LogMonitor/LogMonitor/second/gumtree/java/SayHello.java";
	    String new_file = "/usr/info/code/cpp/LogMonitor/LogMonitor/second/gumtree/java/SayHelloWorld.java";*/
		GumTreeApi g = new GumTreeApi();
		g.getAction(old_file, new_file);
	}
	
	public void getMapping(String filename1, String filename2)
	{
		Run.initGenerators();
		try {//			parse to get tree info
			TreeContext oldTreeContext = Generators.getInstance().getTree(filename1);
			TreeContext newTreeContext = Generators.getInstance().getTree(filename2);
			ITree oldTree = oldTreeContext.getRoot();
			ITree newTree = newTreeContext.getRoot(); 
//			match two trees
			Matcher m = Matchers.getInstance().getMatcher(oldTree, newTree);
			m.match();
			Iterator<Mapping> mappingIter = m.getMappings().iterator();
			ITree srcNode, dstNode;
			while(mappingIter.hasNext())
			{
				Mapping mapping = mappingIter.next();
				srcNode = mapping.getFirst();
				dstNode = mapping.getSecond();
				System.out.printf("1) src info. type:%s, value:%s, line:%d \n", oldTreeContext.getTypeLabel(srcNode), srcNode.getLabel(), getLineNumber(srcNode.getPos(), filename1));
				System.out.printf("2) dst info. type:%s, value:%s, line:%d \n", newTreeContext.getTypeLabel(dstNode), dstNode.getLabel(), getLineNumber(dstNode.getPos(), filename2));
			}
//			generate actions
			ActionGenerator actionGenerator = new ActionGenerator(oldTree, newTree, m.getMappings());
			actionGenerator.generate();
			List<Action> actions = actionGenerator.getActions();
			System.out.printf("3) element edit distance: %d \n", actions.size());
		}
		catch(UnsupportedOperationException | IOException e) {
				e.printStackTrace();
		}
	}

	
	public void getAction(String oldFile, String newFile)
	{
		Run.initGenerators();
		try {
//			parse to get tree info
			TreeContext oldTreeContext = Generators.getInstance().getTree(oldFile);
			TreeContext newTreeContext = Generators.getInstance().getTree(newFile);
			ITree oldTree = oldTreeContext.getRoot();
			ITree newTree = newTreeContext.getRoot(); 
//			match two trees
			Matcher m = Matchers.getInstance().getMatcher(oldTree, newTree);
			m.match();
			m.getMappings();
//			generate actions
			ActionGenerator actionGenerator = new ActionGenerator(oldTree, newTree, m.getMappings());
			actionGenerator.generate();
			List<Action> actions = actionGenerator.getActions();
//			parse actions according to type
			Action action;
			ITree tempNode;
			for(Iterator<Action> iter = actions.iterator(); iter.hasNext(); )
			{
				action = iter.next();		
//				change type
				String changeType = action.getName();
				System.out.printf("1) change info. change type: %s \n", changeType);
//				value and loc info
				String oldValue = "";
				String newValue = "";
				int oldLoc = -1;
				int newLoc = -1;
				switch(changeType)
				{
//				INSERT: new value, new loc
				case "INS":
					tempNode = action.getNode();
					newValue = tempNode.getLabel();
					newLoc = getLineNumber(tempNode.getPos(), newFile);
					break;
//				UPDATE: old / new value; old loc[old value and old loc by default]
				case "UPD":
					newValue = ((Update)action).getValue();
//				MOVE/DELETE: old value, old loc
				default:
					tempNode = action.getNode();	
					oldValue = tempNode.getLabel();
					oldLoc = getLineNumber(tempNode.getPos(), oldFile);
					break;
				}
				System.out.printf("2) old info. value: %s, line: %d \n", oldValue, oldLoc);
				System.out.printf("3) new info. value:%s, line:%d \n", newValue, newLoc);
				System.out.println("******************************************************");
			}
		} catch (UnsupportedOperationException | IOException e) {
			e.printStackTrace();
		}
	}
	
	int getLineNumber(int characterPos, String filename) throws IOException
	{
		LineNumberReader lineReader = new LineNumberReader(new FileReader(filename));
		lineReader.skip(characterPos);
		
		int lineNumber = lineReader.getLineNumber() + 1;
//		System.out.println(lineReader.readLine());
		lineReader.close();
		
		return lineNumber;
	}
	
	String getValue(int beginPos, int endPos, String filename) throws IOException
	{
		FileReader fileReader = new FileReader(filename);
		fileReader.skip(beginPos);
		
		char[] value = new char[100];
		fileReader.read(value, 0, endPos - beginPos);
		fileReader.close();
		
		return String.valueOf(value).trim();
	}
	
}
