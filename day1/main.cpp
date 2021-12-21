#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

/*
	@input The path of the input file
	@output A vector with all the values of the input file
 */
auto get_vector_from_input_file(const std::string& input_file_path)
{
	auto input_vector = std::vector<int>();
	auto input_stream = std::ifstream(input_file_path); // create a stream from the input file
	for (std::string line; std::getline(input_stream, line); )
	{
		input_vector.push_back(std::stoi(line));
	}
	return input_vector;
}

/*
	@input A vector of depths values
	@output The vector of values agglomerated 3 by 3
 */
auto agglomerate_depth_values3(const std::vector<int>& depths)
{
	auto agglomerated_depths = std::vector<int>();
	for (auto it = std::begin(depths); it != std::end(depths)-2; ++it)
	{
		agglomerated_depths.push_back(std::accumulate(it, it+3, 0));
	}
	return agglomerated_depths;
}

/*
	@input A vector of depth numbers
	@output The number of times the depths increased
 */
auto count_depth_increases(const std::vector<int>& input)
{
	auto depth_increases = 0;
	auto last_depth = std::numeric_limits<int>::max();
	for (auto& depth : input)
	{
		if(depth - last_depth > 0)
			depth_increases++;
		last_depth = depth;
	}
	return depth_increases;
}

int main(int argc, char *argv[])
{
	if (argc != 2) { return EXIT_FAILURE; }
	else
	{
		// Getting the full path of the input file
		std::string current_path = std::filesystem::current_path().string();
		std::string input_file_path = current_path + "/" + argv[1];

		std::cout << count_depth_increases(get_vector_from_input_file(input_file_path)) << '\n'; // day 1 part 1 answer
		std::cout << count_depth_increases(agglomerate_depth_values3(get_vector_from_input_file(input_file_path))) << '\n';
	}
	return EXIT_SUCCESS;
}
