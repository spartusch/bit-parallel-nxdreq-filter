/**
 * @author Stefan Partusch
 * @copyright (c) 2008 Stefan Partusch
 */

#include <iostream>
#include "BitParallelHumDomainReqFilter.hpp"

int main() {
	BitParallelHumDomainReqFilter filter;

	std::ios_base::sync_with_stdio(false);

	filter.filter(std::cin);

	return 0;
}
