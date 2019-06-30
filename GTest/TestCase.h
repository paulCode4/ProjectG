#pragma once

#include <stdio.h>
#include <string>

#define RUN_TEST(p)\
    if( setUp(#p) == 0) \
    { \
        printf("Running Test: %s\n", #p); \
        int numFails = m_numFailedAssertions;  \
        p(); \
        if(m_numFailedAssertions != numFails)  \
            m_numFailedTests ++; \
        if(m_numAssertionsInTest == 0)   \
         printf("    Test does not have any assertions\n"); \
        m_numAssertions += m_numAssertionsInTest;   \
        m_numTests ++;  \
        m_numAssertionsInTest = 0;\
        tearDown(#p); \
    }
    
    
#define ASSERT_EQUALS(a, b)\
    m_numAssertionsInTest ++; \
    if (a != b) \
    {           \
        printf("    [%s] should have been equal with [%s]\n", #a, #b); \
        printf("        Line %i at %s\n", __LINE__, __FILE__); \
        m_numFailedAssertions++;            \
    }   

#define ASSERT_NOT_EQUALS(a, b)\
    m_numAssertionsInTest ++; \
    if (a == b) \
    {           \
        printf("    [%s] should not have been equal with [%s]\n", #a, #b); \
        printf("        Line %i at %s\n", __LINE__, __FILE__); \
        m_numFailedAssertions++;            \
    }   

    
class TestCase
{
public:
    TestCase()
    : m_numFailedAssertions(0)
    , m_numFailedTests(0)
    , m_numTests(0)
    , m_numAssertions(0)
    , m_numAssertionsInTest(0)
    {
    }
    
    virtual ~TestCase()
    {
    }
    
    /**
     * Will be called by user to trigger the tests. It will return 
     * number of failed assertions
     */
    int execute()
    {
        run();
        //
        //Print how many test executed and how many assertions
        //
        printf("%i tests are failed out of %i tests (%i assertions failed out of %i) \n", m_numFailedTests, m_numTests, m_numFailedAssertions, m_numAssertions);
        
        return m_numFailedAssertions;
    }
    
protected:
    /**
     * Use RUN_TEST macro to execute the test methods in run()
     * This macro will invoke setUp() method prior to each test passing 
     * the test name and tearDown() after
     */
    virtual void run()
    {
    }
    
    /**
     * Will be invoked before the actual test method by the RUN_TEST macro.
     * Return 0 means test can continue, anythin other is fail code and test 
     * will not be invoked
     */
    virtual int setUp(const std::string& iTestName)
    {
        printf("   setUp(%s)\n", iTestName);
        return 0;
    }
    
    /**
     * Will be invoked after the test
     */
    virtual void tearDown(const std::string& iTestName)
    {
        printf("   tearDown(%s)\n", iTestName);
    }
    
    int m_numFailedAssertions;    
    int m_numFailedTests;
    int m_numTests;
    int m_numAssertions;
    int m_numAssertionsInTest;
};
