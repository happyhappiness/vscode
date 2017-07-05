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
import java.io.LineNumberReader;

public class GumTreeApi {
	
	public static void main(String args[])
	{
		System.out.println("hello I am gumtree api");
	}
	
	public void getMapping(String filename1, String filename2)
	{
		Run.initGenerators();
		try {
//			parse to get tree info
			ITree oldFile = Generators.getInstance().getTree(filename1).getRoot();
			ITree newFile = Generators.getInstance().getTree(filename2).getRoot(); 
//			match two trees
			Matcher m = Matchers.getInstance().getMatcher(oldFile, newFile);
			m.match();
			Iterator<Mapping> mappingIter = m.getMappings().iterator();
			ITree srcNode, dstNode;
			while(mappingIter.hasNext())
			{
				Mapping mapping = mappingIter.next();
				srcNode = mapping.getFirst();
				dstNode = mapping.getSecond();
				System.out.printf("1) src info. type:%s, value:%s, line:%d \n", srcNode.getType(), srcNode.getLabel(), getLineNumber(srcNode.getPos(), filename1));
				System.out.printf("2) dst info. type:%s, value:%s, line:%d \n", dstNode.getType(), dstNode.getLabel(), getLineNumber(dstNode.getPos(), filename2));
			}
//			generate actions
			ActionGenerator actionGenerator = new ActionGenerator(oldFile, newFile, m.getMappings());
			actionGenerator.generate();
			List<Action> actions = actionGenerator.getActions();
			System.out.printf("3) element edit distance: %d \n", actions.size());
		}
		catch(UnsupportedOperationException | IOException e) {
				e.printStackTrace();
		}
	}

	
	public void getAction(String filename1, String filename2)
	{
		Run.initGenerators();
		try {
//			parse to get tree info
			ITree oldFile = Generators.getInstance().getTree(filename1).getRoot();
			ITree newFile = Generators.getInstance().getTree(filename2).getRoot(); 
//			match two trees
			Matcher m = Matchers.getInstance().getMatcher(oldFile, newFile);
			m.match();
			m.getMappings();
//			generate actions
			ActionGenerator actionGenerator = new ActionGenerator(oldFile, newFile, m.getMappings());
			actionGenerator.generate();
			List<Action> actions = actionGenerator.getActions();
			int n = actions.size();
//			parse actions according to type
			Action action;
			ITree srcNode, dstNode;
			for(int i = 0; i < n; i++)
			{
				action = actions.get(i);
			
//				change type
				String changeType = action.getName();
				System.out.printf("1) change info. change type: %s \n", changeType);
//				dst info
				String type = "";
				String value = "";
				int lineNumber = -1;
				switch(changeType)
				{
				case "UPD":
					srcNode = action.getNode();
					value = ((Update)action).getValue();
					break;
				case "MOV":
				case "INS":
					srcNode = ((Addition)action).getParent();
					dstNode = action.getNode();
					type =  String.valueOf(dstNode.getType());
					value = dstNode.getLabel();
					lineNumber = getLineNumber(dstNode.getPos(), filename2);
					break;
				default:
					srcNode = action.getNode();
					break;
				}
				System.out.printf("2) src info. type:%s, value: %s, line: %d \n", srcNode.getType(), srcNode.getLabel(), getLineNumber(srcNode.getPos(), filename1));
				System.out.printf("3) dst info. type:%s, value:%s, line:%d \n", type, value, lineNumber);
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
	
}
