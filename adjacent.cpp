#include "adjacent.h"

bool adjacent::compareAdj(const adjacent& first, const adjacent& second)
{
	return (first.vertex < second.vertex);
}
