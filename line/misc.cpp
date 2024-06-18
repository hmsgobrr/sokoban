#include "misc.h"

Warna::Warna(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	dat = (r << 24) | (g << 16) | (b << 8) | a;
}

unsigned int Warna::data() {
	return dat;
}

unsigned char Warna::r() {
	return (dat & (255 << 24)) >> 24;
}

unsigned char Warna::g() {
	return (dat & (255 << 16)) >> 16;
}

unsigned char Warna::b() {
	return (dat & (255 << 8)) >> 8;
}

unsigned char Warna::a() {
	return dat & 255;
}
