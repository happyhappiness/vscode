package gumtree;
import java.io.FileReader;
import java.io.IOException;
import java.util.List;

import com.github.gumtreediff.actions.ActionGenerator;
import com.github.gumtreediff.actions.model.Action;
import com.github.gumtreediff.actions.model.Addition;
import com.github.gumtreediff.actions.model.Delete;
import com.github.gumtreediff.actions.model.Update;
import com.github.gumtreediff.client.Run;
import com.github.gumtreediff.gen.Generators;
import com.github.gumtreediff.matchers.Matcher;
import com.github.gumtreediff.matchers.Matchers;
import com.github.gumtreediff.tree.ITree;
import java.io.LineNumberReader; 

public class SayHello {
	
	public static void main(String args[]) throws UnsupportedOperationException, IOException
	{
		Run.initGenerators();
		String file1 = "/data/download/CMake/CMake/Kitware_CMake_00_new.cpp";
		String file2 = "/data/download/CMake/CMake/Kitware_CMake_00_old.cpp";
		ITree src = Generators.getInstance().getTree(file1).getRoot();
		ITree dst = Generators.getInstance().getTree(file2).getRoot(); 
		Matcher m = Matchers.getInstance().getMatcher(src, dst);
		m.match();
		m.getMappings();
		ActionGenerator actionGenerator = new ActionGenerator(src, dst, m.getMappings());
		actionGenerator.generate();
		List<Action> actions = actionGenerator.getActions();
		int n = actions.size();
		
		// try to understand each action
		Action curr;
		for(int i = 0; i < n; i++)
		{
			curr = actions.get(i);
			switch(curr.getName())
			{
			case "UPD":
				System.out.println(((Update)curr).toString());
				break;
			case "DEL":
				System.out.println(((Delete)curr).toString());
				break;
			case "MOV":
			case "INS":/*
				System.out.println(((Addition)curr).toString());*/
				break;
			default:
					break;
			}
			// src info
			ITree srcNode = curr.getNode();
			
			LineNumberReader lineReader = new LineNumberReader(new FileReader(file1));
			lineReader.skip(srcNode.getPos());
			System.out.println("change type:" + curr.getName() + ";Line" + lineReader.getLineNumber() + ":" + lineReader.readLine());
			// dst info
			
			lineReader.close();
		}
	}
	
}
