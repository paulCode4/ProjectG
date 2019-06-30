

#include "stdio.h"


#include "TestGraph.h"
#include "TestNode.h"
#include "TestObjectTracker.h"

int foo(void)
{
    printf("foo\n");
    return 0;
}

struct TestData
{
    std::string name;
    TestCase *pTestCase;
};

int main(int argc, char* argv[])
{
    printf("GTest.exe\n");
    
    TestData testList[] = {
        {"TestGraph", new TestGraph()},
        {"TestNode", new TestNode()},
        //{"TestObjectTracker", new TestObjectTracker()},
        {"", 0}
    };
    
    int numFails = 0;
    for(int i = 0; testList[i].pTestCase; i++)
    {
        printf("===============================================================\n");
        printf("= Executing [%s]\n", testList[i].name.c_str());
        printf("===============================================================\n");
        numFails = testList[i].pTestCase->execute();
        delete testList[i].pTestCase;
        testList[i].pTestCase = NULL;
        if(numFails > 0)
        {
            printf ("Test Case [%s] is failed, you have to fix it to continue\n", 
                testList[i].name.c_str());
            break;
        }
    }
    
    return numFails;
}