#pragma once

int difBlock(int x, int y)
{
	return (x * y) % 4;
}

uint64_t difBlock(uint64_t x, uint64_t y)
{
    uint64_t h = x * 0x9E3779B97F4A7C15ULL + y;
    h ^= h >> 33;
    h *= 0xff51afd7ed558ccdULL;
    h ^= h >> 33;
    h *= 0xc4ceb9fe1a85ec53ULL;
    h ^= h >> 33;
    int w = h % 4;
    return w;
}
