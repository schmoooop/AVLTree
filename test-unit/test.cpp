//#include "../src/AVLTree.h"
//#include <stdlib.h>
//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
//
//TEST_CASE("Incorrect Commands", "[flag]"){
//    AVLTree inputTree;
//    inputTree.insertNameID("Eren Yeager", "33466548");
//    std::vector<string> expectedOutput = ;
//    REQUIRE(expectedOutput );
//}
//
//
//TEST_CASE("BST Insert Large", "[flag]"){
//    AVLTree inputTree;
//    std::vector<int> expectedOutput, actualOutput;
//
//    for(int i = 0; i < 100000; i++)
//    {
//        int randomInput = rand();
//        if (std::count(expectedOutput.begin(), expectedOutput.end(), randomInput) == 0)
//        {
//            expectedOutput.push_back(randomInput);
//            inputTree.insert(randomInput);
//        }
//    }
//
//    actualOutput = inputTree.inorder();
//    REQUIRE(expectedOutput.size() == actualOutput.size());
//    REQUIRE_FALSE(expectedOutput == actualOutput);    //This assertion can be wrong. Don't use
//    std::sort(expectedOutput.begin(), expectedOutput.end());
//    REQUIRE(expectedOutput == actualOutput);
//
//}
//
