#include <catch.hpp>
#include "graph.cpp"

TEST_CASE("graph1")
{
  string input {
     "1 1 1 1 1\n"
     "1 1 1 1 1\n"
     "1 1 1 1 1\n"
     "1 1 1 1 1\n"
     "1 1 1 1 1\n"
    };
  
  string result = "1 0 2 3 4 ";
  
  graph Graph(5);
  Graph.read_mtrx(input);
  
  std::ostringstream ostream;
  Graph.graph_dfs(ostream, 1);
  
  REQUIRE(ostream == result);
}

TEST_CASE("wrong size")
{
  string input {
     "1 1 1\n"
     "1 1 1\n"
     "1 1 1\n"
    };
  graph Graph(3);
  Graph.read_mtrx(input);
  
  REQUIRE_THROWS(Graph.graph_dfs(ostream, 5););
}
