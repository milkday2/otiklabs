#include <cstdint>

unsigned char* int2lendian(uint32_t value) {
	static unsigned char nc[4];
	nc[0] = (value >> 0) & 0xFF;
	nc[1] = (value >> 8) & 0xFF;
	nc[2] = (value >> 16) & 0xFF;
	nc[3] = (value >> 24) & 0xFF;
	return nc;
}

unsigned char* sint2lendian(uint16_t value) {
	static unsigned char nc[2];
	nc[0] = (value >> 0) & 0xFF;
	nc[1] = (value >> 8) & 0xFF;
	return nc;
}

uint32_t lendian2int(unsigned char* c) {
	return c[0] | c[1] << 8 | c[2] << 16 | c[3] << 24;
}
uint16_t lendian2sint(unsigned char* c) {
	return c[0] | c[1] << 8;
}