#coding:utf-8
from jpype import *
import os

def simple_test():
    """"simple test about invoking jdk methods"""

    startJVM(getDefaultJVMPath(), '-ea')
    java.lang.System.out.println("hello java in python")
    shutdownJVM()

def jar_test():
    """"test about invoke packaged jar"""
    jarpath = os.path.join(os.path.abspath('.'), '/ust/info/code/cpp/LogMonitor/LogMonitor/java/test.jar')
    startJVM(getDefaultJVMPath(), "-ea", "-Djava.class.path=%s" % jarpath)
    Test = JClass('GumTreeUse.src.gumtree.SayHello')
    # 或者通过JPackage引用Test类
    # com = jpype.JPackage('com')
    # Test = com.Test
    t = Test()
    t.main('a')
    shutdownJVM()

jar_test()
