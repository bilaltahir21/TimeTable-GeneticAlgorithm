#pragma once
#include <vector>

/*
 * Following map is designed to pre-process
 * data of the gene to know aid in finding
 * clashes
 */

class HashMap {
public:
	std::vector<std::vector<int>> hash;

	HashMap() = default;

	explicit HashMap(const int size) { hash.resize(size); }

	int entriesCount(const int index) { return int(hash.at(index).size()); }
};
