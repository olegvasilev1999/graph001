#include <catch.hpp>
#include <sstream>
#include "graph.cpp"


using namespace std;

TEST_CASE("graph1")
{
  string input {
     "1 1 1 1 1\n"
     "1 1 1 1 1\n"
     "1 1 1 1 1\n"
     "1 1 1 1 1\n"
     "1 1 1 1 1\n"
    };
  istringstream stream (input);
  
  string result = "1 0 2 3 4 ";
  
  graph Graph(5);
  Graph.read_mtrx(stream);
  
  ostringstream ostream;
  Graph.graph_dfs(ostream, 1);
  
   REQUIRE(result == ostream.str());
}

TEST_CASE("wrong size")
{
  string input {
     "1 1 1\n"
     "1 1 1\n"
     "1 1 1\n"
    };
  istringstream stream (input);
  
  graph Graph(3);
  Graph.read_mtrx(stream);
  
   ostringstream ostream;
  
  REQUIRE_THROWS(Graph.graph_dfs(ostream, 5));
}

TEST_CASE("way")
{
  string input {
     "0 1 1 1\n"
     "1 0 0 1\n"
     "1 0 0 0\n"
     "1 1 0 0\n"
    };
  istringstream stream (input);
  
  string result {
    "1 0 \n"
    "1 \n"
    "1 0 2 \n"
    "1 3 \n"
  };
  
  graph Graph(4);
  Graph.read_mtrx(stream);
  
  ostringstream ostream;
  Graph.shortway(ostream, 1);
  
   REQUIRE(result == ostream.str());
}
